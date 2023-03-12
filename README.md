version:[2023-03-12]    
# Игра для кодеров - Чей ИИ умней?!

 СТАТУС:  юзабельно.
 
 https://www.cyberforum.ru/cpp-beginners/thread3086648.html
 
 Тут Code::Blocks проект
 для Арбитра, который будет судить в турнире по кресто-ноликам среди участников,
 написавших свой Искусственный Интеллект(смотри проект 'ai_cpp_dll')
 

## Как оно:

1. Нужно написать код играющий за бота, который принимает на вход поле с фишками
 и принимающий решение куда поставить свою фишку, т.е. возвращающий координаты
 своего хода.
 
2. Код компилируется как ДЛЛ библиотека.
 
3. Может быть много ботов. Все они должны находиться с exe программой,
 которая будет представлять собой Арбитра, который берет на себя организацию 
 турнира между ботами представленными ДЛЛ'ками.
 
4. Игра между двумя ботами проходит в ДВА матча.
 В первом матче игру начинает первый бот, а во втором матче игру начинает второй бот.
 
5. Турнир организовывается по схеме(дефолтная) ВСЕ ИГРАЮТ СО ВСЕМИ.
 т.е. для 3 ботов будет всего 6 матчей(игр).
 
6. По окончании турнира вывешивается итоговая таблица РЕЙТИНГОВ. 
 - за победу +2 очка.
 - за ничью +1 очко.
 - за проигрыш ничаво.
 - за фейл  дисквалификация [пока не реализован]

 
## Изменения:
 
Изменения[2023-03-09]:
+ добавлено свойство last_step
+ игровое поле размещается локально(у игрока нет доступа к полю Арбитра)

Изменения[2023-03-11]:
+ разбит на хедеры
+ добавлены режима: автопауза, быстрый, стоп-шаг

Изменения[2023-03-12]:
+ формирование любой расстановки на доске из файла

