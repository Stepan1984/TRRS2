# TRRS1 — Matrix7

![CI/CD Pipeline](https://github.com/Stepan1984/TRRS1/actions/workflows/ci.yml/badge.svg)

Вариант 20. Квадратная матрица порядка 7.

Программа находит:
- количество нулевых элементов выше главной диагонали
- количество положительных элементов ниже побочной диагонали

Если количества равны — обнуляет всю матрицу.

## Структура проекта

```
.
├── .github/workflows/ci.yml   # CI/CD пайплайн (GitHub Actions)
├── DEBIAN/control             # Метаданные deb-пакета
├── cicd/
│   ├── build.sh               # Скрипт сборки
│   ├── test.sh                # Скрипт тестирования
│   └── package.sh             # Скрипт упаковки в .deb
├── source/
│   ├── main.c                 # Исходный код
│   └── Makefile               # Makefile
└── usr/bin/                   # Собранный бинарник (gitignored)
```

## CI/CD пайплайн

Пайплайн состоит из 4 стейджей:

| Стейдж   | Описание                                              |
|----------|-------------------------------------------------------|
| build    | Сборка через `make`, артефакт: `usr/bin/matrix7`     |
| test     | Shell-тесты бинарника                                 |
| package  | Сборка `.deb` пакета, артефакт: `pkg/trrs1_1.0.deb` |
| release  | Создание GitHub Release с `.deb` файлом              |

## Сборка вручную

```bash
bash cicd/build.sh
bash cicd/test.sh
bash cicd/package.sh
```
