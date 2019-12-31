#include <rtthread.h>
#include <stdio.h>
#include <string.h>
#include "capnp_c.h"
#include "myschema.capnp.h"

static capn_text chars_to_text(const char *chars) {
  return (capn_text) {
    .len = (int) strlen(chars),
    .str = chars,
    .seg = NULL,
  };
}

void capnp_encode_to_file_entry(void* parameters)
{
  uint8_t buf[4096];
  ssize_t sz = 0;

  const char *name = "Han Wu";
  const char *email = "wuhanstudio@domain.com";
  const char *school = "Huazhong Univ. of Sci. and Tech.";

  printf("--- Encoding ---\n");
  {
    // Init memory
    struct capn c;
    capn_init_malloc(&c);

    // Get capn object
    capn_ptr cr = capn_root(&c);
    struct capn_segment *cs = cr.seg;

    // Set Person
    struct Person p = {
      .id = 17,
      .name = chars_to_text(name),
      .email = chars_to_text(email),
    };

    // Set employment
    p.employment_which = Person_employment_school;
    p.employment.school = chars_to_text(school);

    // Set PhoneNumber lists
    p.phones = new_Person_PhoneNumber_list(cs, 2);

    struct Person_PhoneNumber pn0 = {
      .number = chars_to_text("+8612345678900"),
      .type = Person_PhoneNumber_Type_work,
    };
    set_Person_PhoneNumber(&pn0, p.phones, 0);

    struct Person_PhoneNumber pn1 = {
      .number = chars_to_text("+8613579246800"),
      .type = Person_PhoneNumber_Type_home,
    };
    set_Person_PhoneNumber(&pn1, p.phones, 1);

    // Write Person to Capnp
    Person_ptr pp = new_Person(cs);
    write_Person(&p, pp);
    capn_setp(cr, 0, pp.p);

    // Write to memory
    sz = capn_write_mem(&c, buf, sizeof(buf), 0 /* packed */);

    capn_free(&c);
  }

  printf("\n");

  printf("--- Write to File ---\n");	
  {	
    // Write serialized object to file system.	
    FILE *f = fopen("/person.bin", "wb");	
    fwrite(buf, 1 /* size */, sz /* count */, f);	
    fclose(f);	
  }

  printf("\n");
}

static void capnp_encode_to_file(int argc,char *argv[])
{
    rt_thread_t thread = rt_thread_create("capnp", capnp_encode_to_file_entry, RT_NULL, 10240, 25, 10);
    if(thread != RT_NULL)
    {
        rt_thread_startup(thread);
        rt_kprintf("[capnp] New thread capnp\n");
    }
    else
    {
        rt_kprintf("[capnp] Failed to create thread capnp\n");
    }
}
MSH_CMD_EXPORT(capnp_encode_to_file, capnp encode to file example)
