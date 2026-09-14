# Project Algorytmy i Struktury Danych II
Matvii Milyutin

## Temat projektu
Na projekt zaliczeniowy postanowiłem utworzyć [parser formatu JSON](https://github.com/Chackapon/json_parser_cpp/tree/main), aby móc ładować zapisane do pliku grafy z powrotem do programu.

Problem serializacji grafu do pliku jest dość łatwy do rozwiązania i moje klasy implementujące grafy już posiadają funkcje temu służące. Znacznie trudniejszym jest utworzenie parsera w języku ze statycznym typowaniem, gdzie w JSON wartości mogą być kilku różnych typów, w tym wielokrotnie zagnieżdżonych list i obiektów (słowników).
Udało mi się rozwiązać ten problem posługując się std::variant

## Jak skompilować projekt

> make run
