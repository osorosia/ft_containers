# ft_containers

42 (https://42.fr/en/homepage/) の課題として、C++98のSTLのコンテナであるvectorとmapを再実装しました。

要件として下記が指定されています。
- 名前空間をftとする
- 全てのmember functions, non-member functions, overloadsを実装する
- 本家STLより20倍以上遅くならない
- 十分なテストを用意する
- メモリリーク禁止

cppreference.com (https://en.cppreference.com/w/) のC++98/03の仕様に則って再実装しました。

```sh
$ c++ -v
gcc version 11.3.0 (Ubuntu 11.3.0-1ubuntu1~22.04)

# unit test
$ make unit
          vector: OK
             map: OK
            pair: OK
       enable_if: OK
           equal: OK
     is_integral: OK
reverse_iterator: OK
        avl_tree: OK

# benchmark test
$ make bench
```
