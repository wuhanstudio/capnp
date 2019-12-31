## Cap'n Proto

![](https://capnproto.org/images/logo.png)

### Protobuf

为了更高效地存储数据，可以利用 Google 的 protobuf 定义二进制数据格式，例如下面的 proto 定义了一种二进制的文件格式，并且可以自动生成解析二进制文件的源码，现在支持十多种语言。

```
syntax = "proto3";

message AMessage {
  int32 a=1; 
  int32 b=2;
}
```

关于 protobuf 这里就不做过多介绍了，RT-Thread 也有 [protobuf-c](https://github.com/wuhanstudio/protobuf-c) 软件包。



### Capnp

同样的道理，capnp 也是为了更加高效地存储数据，但是相比 Google 的 protobuf 更加高效，更加轻量级。

![capnp](https://capnproto.org/images/infinity-times-faster.png)

capnp 也支持很多种不同的编程语言，如果想生成 C 源码的话，和 protobuf 一样，可以先安装插件。

```
git clone https://github.com/opensourcerouting/c-capnproto
cd c-capnproto
git submodule update --init --recursive
autoreconf -f -i -s
./configure
make
make install
```

例如下面定义了一种二进制文件格式：

```
@0x9eb32e19f86ee174;

using C = import "c.capnp";
$C.fieldgetset;

struct Person {
  id @0 :UInt32;
  name @1 :Text;
  email @2 :Text;
  phones @3 :List(PhoneNumber);

  struct PhoneNumber {
    number @0 :Text;
    type @1 :Type;

    enum Type {
      mobile @0;
      home @1;
      work @2;
    }
  }

  employment :union {
    unemployed @4 :Void;
    employer @5 :Text;
    school @6 :Text;
    selfEmployed @7 :Void;
    # We assume that a person is only one of these.
  }
}

struct AddressBook {
  people @0 :List(Person);
}
```

把上面的文件保存为 myschema.capnp 后可以生成 C 源码：

```
capnp compile -o ./capnpc-c myschema.capnp
```

关于解析的例程可以查看 examples 目录。



## 联系方式

- 维护：Wu Han
- 主页：[http://wuhanstudio.cc](http://wuhanstudio.cc/)
- 邮箱：[wuhanstudio@qq.com](mailto:wuhanstudio@qq.com)