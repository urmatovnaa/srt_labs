# Лабораторные работы по Системам Реального Времени

**Дисциплина:** Системы реального времени  
**Студентка:** Кубанычева А, 3 курс  
**Группа:** МО 2-группа  
**Год:** 2025

## Стандартная сборка
```bash
# Для каждой лабораторной:
cd labX                 
# Debug режим
mkdir build_debug && cd build_debug
cmake -DCMAKE_BUILD_TYPE=Debug .. && make && ./labX

# Release режим
mkdir ../build_release && cd ../build_release
cmake -DCMAKE_BUILD_TYPE=Release .. && make && ./labX
```