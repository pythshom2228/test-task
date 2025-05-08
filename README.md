
### Функциональность

* Открытие / закрытие смены
* Ведение кассовых чеков
* Поддержка наличных и оплаты картой
* Выдача сдачи
* Печать чека и итогов смены
* Хранение и поиск товаров (по имени и штрихкоду)

### Технологии

* Язык: **C++14**
* Сборка: **CMake**
* Зависимости:

  * [nlohmann/json](https://github.com/nlohmann/json) — для работы с товарной базой
  * [GoogleTest](https://github.com/google/googletest) — для юнит-тестов


### Сборка проекта

#### Требования

* CMake 3.14+
* g++ (или другой компилятор с поддержкой C++14)
* git

#### Сборка

```bash
git clone <repo>
cd <repo>
mkdir build
cmake -B build
cmake --build build
```

### Запуск

```bash
./build/rmk products
```

### Тестирование

```bash
cmake --build build --target unit_tests
./build/unit_tests
```