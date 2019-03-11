# Nm-otool

Disclaimer
----------
> In School 42, almost every project must be written according to a coding syntax standard (also known as "[Norme](./docs/norme.fr.pdf)").
>
> That's why some parts may be strange

About
-----
> Let's analyze the format of MacOS executables and understand how the kernel launches the binaries, by rewriting these two system tools. Essential for all those who want to make security, this project is more generally an opening on the UNIX culture system.

This is the second project of the Advanced Unix branch at School 42 Paris

Installation
------------
Run `make fclean && make`

Usage
-----
`./ft_nm [file ...]`

`./ft_otool [file ...]`

### Example
```
> ./ft_nm tests/test_facile
0000000100000000 T __mh_execute_header
0000000100000f60 T _main
                 U _puts
                 U dyld_stub_binder
```

```
> ./ft_otool tests/test_facile
tests/test_facile:
Contents of (__TEXT,__text) section
0000000100000f60	55 48 89 e5 48 83 ec 10 48 8d 3d 3b 00 00 00 c7
0000000100000f70	45 fc 00 00 00 00 e8 0d 00 00 00 31 c9 89 45 f8
0000000100000f80	89 c8 48 83 c4 10 5d c3
```

##### Project done in 2018
