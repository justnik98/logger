# Потокобезопасный header-only логгер с++ 

## Как использовать

### Настройки ###
```cpp
int Logger::cur_log_lvl = DEBUG; // уровень логирования (ERROR, WARNING, INFO, DEBUG)
std::string Logger::log_file = "out"; // выходной файл для логов, по умолчанию ./out
uint32_t Logger::max_file_size = 2 << 30; // максимальный размер хранимых логов, по умолчанию 1ГБ
```

### Вывод сообщений в лог
```cpp
LOG_ERROR() << "Some Error msg"; // выводит сообщение об ошибке
LOG_WARNING() << "Some Warning msg"; // выводит сообщение о предпреждении
LOG_INFO() << "Some Info msg"; // выводит сообщение о предпреждении
LOG_DEBUG() << "Some Info msg"; // выводит сообщения для отладки
```

### Пример вывода
```
[ERROR] 2022-07-24 16:30:41  Some Error msg
[WARNING] 2022-07-24 16:30:41  Some Warning msg
[INFO] 2022-07-24 16:30:41  Some Info msg
[DEBUG] 2022-07-24 16:30:41  Some Info msg
```
