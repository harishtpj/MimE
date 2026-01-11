# MimE - Minimal Email Server
[![using-c](https://img.shields.io/badge/Using-C%20-blue)](https://gcc.gnu.org/)

Welcome to the **MimE** project, a simple, local mail server written from scratch in C.

# About

MimE is a high-performance, lightweight Mail Server built entirely from scratch using C. This project implements the core mechanics of email transmission, focusing on the SMTP (Simple Mail Transfer Protocol) to handle message routing and delivery.

The `mime` server currently have these features:
- Built-in handling of SMTP commands (`HELO`, `MAIL FROM`, `RCPT TO`)
- Created using socket programming based on Berkeley sockets API (BSD Sockets).
- Has no other dependencies other than `libc`

# Requirements

Since the project uses BSD Sockets API, this application is currently supported only on Linux based platforms. For windows, try using WSL.

To build the server, run
```
$ git clone https://github.com/harishtpj/MimE
$ cd MimE
$ make build_smtp
```

now you can start the server by running
```
$ mime
```

or you could directly run it by
```
$ make run_smtp
```

# 📝 License

#### Copyright © 2022 [M.V.Harish Kumar](https://github.com/harishtpj). <br>

#### This project is [MIT](https://github.com/harishtpj/MimE/blob/master/LICENSE) licensed.
