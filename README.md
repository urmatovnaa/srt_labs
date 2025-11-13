## Лабораторные работы по Системам Реального Времени

**Дисциплина:** Системы реального времени  
**Студентка:** Кубанычева А, 3 курс  
**Группа:** МО 2-группа  
**Год:** 2025


### Стандартная сборка
```bash
# Для каждой лабораторной:
cd labX                 
mkdir build && cd build
cmake ..               
make                   
./labX                 
```
**Режимы сборки**
```bash
# Debug режим (отладка)
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
./lab1_debug
# Release режим (производительность)
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./lab1_release
```
