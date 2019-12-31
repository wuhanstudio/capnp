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

void capnp_decode_from_file_entry(void* parameters)
{
  uint8_t buf[4096];
  ssize_t sz = 0;

  const char *name = "Han Wu";
  const char *email = "wuhanstudio@domain.com";
  const char *school = "Huazhong Univ. of Sci. and Tech.";

  printf("--- Read from File ---\n");	
  {	
    // Read serialized object from file system.	
    FILE *fp;

    // Get File Size
    fp = fopen("/person.bin", "rb"); 
    fseek(fp, 0L, SEEK_END);
    sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    fread(buf, sz, 1, fp);
    fclose(fp);
  }
  printf("\n");

  printf("--- Decoding ---\n");
  {
    struct capn rc;
    int init_mem_ret = capn_init_mem(&rc, buf, sz, 0 /* packed */);

    Person_ptr rroot;
    struct Person rp;

    // Read data out
    rroot.p = capn_getp(capn_root(&rc), 0 /* off */, 1 /* resolve */);
    read_Person(&rp, rroot);

    printf("Person ID: %d\n", rp.id);
    printf("Person Name: %s\n", rp.name.str);
    printf("Person Email: %s\n", rp.email.str);

    switch(rp.employment_which) 
    {
        case Person_employment_unemployed:
            printf("Unemployed\n");
        break;

        case Person_employment_selfEmployed:
            printf("Self Employed\n");
        break;

        case Person_employment_employer:
            printf("Employer: %s\n", rp.employment.employer.str);
        break;

        case Person_employment_school:
            printf("School: %s\n", rp.employment.school.str);
        break;

        default:
        printf("Unknown Employment Status\n");
        break;
    }

    struct Person_PhoneNumber rpn0;
    get_Person_PhoneNumber(&rpn0, rp.phones, 0);
    printf("Phone Number 0: %s\n", rpn0.number.str);

    struct Person_PhoneNumber rpn1;
    get_Person_PhoneNumber(&rpn1, rp.phones, 1);
    printf("Phone Number 1: %s\n", rpn1.number.str);

    capn_free(&rc);
  }
  printf("\n");

  printf("\n");
}

static void capnp_decode_from_file(int argc,char *argv[])
{
    rt_thread_t thread = rt_thread_create("capnp", capnp_decode_from_file_entry, RT_NULL, 10240, 25, 10);
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
MSH_CMD_EXPORT(capnp_decode_from_file, capnp decode from file example)
