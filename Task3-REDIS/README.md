# Общие сведения
Данный проект предназначается для сбора и сохранения статистики о временных затратах на передачу данных с помощью REDIS и SQLite. 
Программа App пересылает данные в Processor, который инкрементирует полученные значения и возвращает их обратно.\
Время каждой операции сохраняется в создаваемую БД Times.bd. Программа циклически (100 раз) пересылает данные из массива длинной 100.
Информация о времени, затраченном на одну итерацию цикла используется для создания гистограммы.
___
# Требумые компоненты
Для работы программы на вашем устройстве должны быть следующие компоненты:
* СУБД REDIS
* Библиотека hiredis
* Библиотека sqlite3
___
# Запуск программы
1. Перейдите в каталог App
2. Создайте в нём папку build и перейдите в неё
3. Из этой папки запустите CMake из родительского каталога (обычно из командной строки cmake ..)
4. При успешном выполнении соберите проект (обычно командой make)
5. Повторите для каталога Processor
6. В папках build у вас будут находиться исполняемые файлы (App и Processor соответственно), запустите сначала Processor, потом App.
7. Дождитесь выполнения программы (показано заполняемой полоской), по окончанию получите гистограмму, среднее и максимальное время загрузки, а также заполненную таблицу в Times.bd
Ожидаемый результат:
   ![image](https://github.com/user-attachments/assets/95718256-fb2b-44ce-8815-5dc99877680d)

