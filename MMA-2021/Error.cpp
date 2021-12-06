#include "stdafx.h"
#include "Error.h"

Error::ERROR errors[ERROR_MAX_ENTRY] =
{
	ERROR_ENTRY(0, "Недопустимый код ошибки"),
	ERROR_ENTRY(1, "Cистемный сбой"),
	ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
	ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),

	ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
	ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),

	ERROR_ENTRY(100, "Параметр -in должен быть задан"),
	ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
	ERROR_ENTRY(104, "Превышена длина входного параметра"),
	ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
	ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),

	ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
	ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
	ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
	ERROR_ENTRY(113, "Ошибка при создании файла выхода (-out)"),
	ERROR_ENTRY_NODEF(114),
	ERROR_ENTRY_NODEF(115),
	ERROR_ENTRY_NODEF(116),
	ERROR_ENTRY_NODEF(117),
	ERROR_ENTRY_NODEF(118),
	ERROR_ENTRY_NODEF(119),

	ERROR_ENTRY(120, "[Лексическая] Превышен максимальный размер таблицы лексем"),
	ERROR_ENTRY(121, "[Лексическая] Таблица лексем переполнена"),
	ERROR_ENTRY(122, "[Лексическая] Нераспознаянная лексема"),
	ERROR_ENTRY(123, "[Лексическая] Выход за пределы таблицы лексем"),
	ERROR_ENTRY_NODEF(124),
	ERROR_ENTRY(125, "[Лексическая] Превышен максимальный размер таблицы идентификаторов"),
	ERROR_ENTRY(126, "[Лексическая] Таблица идентификаторов переполнена"),
	ERROR_ENTRY(127, "[Лексическая] Выход за пределы таблицы идентификаторов"),
	ERROR_ENTRY(128, "[Лексическая] Повторное объявление main"),
	ERROR_ENTRY(129, "[Лексическая] Отсутствие входной точки программы функции main"),
	ERROR_ENTRY_NODEF10(130),
	ERROR_ENTRY_NODEF10(140),
	ERROR_ENTRY_NODEF10(150),
	ERROR_ENTRY_NODEF10(160),
	ERROR_ENTRY_NODEF10(170),
	ERROR_ENTRY_NODEF10(180),
	ERROR_ENTRY_NODEF10(190),

	ERROR_ENTRY_NODEF100(200),

	ERROR_ENTRY(300, "[Cемантическая] Функция main должна возвращать числовое значение"),
	ERROR_ENTRY(301, "[Cемантическая] Тип функции и тип возвращаемого значения отличаются"),
	ERROR_ENTRY(302, "[Cемантическая] Несоответствие типов параметров в вызываемой функции"),
	ERROR_ENTRY(303, "[Cемантическая] Неверное количество параметров вызываемой функции"),
	ERROR_ENTRY(304, "[Cемантическая] Запрещено присваивать значение функции"),
	ERROR_ENTRY(305, "[Cемантическая] Несоответсвие присваимаего типа данных"),
	ERROR_ENTRY(306, "[Cемантическая] Использование имени переменной в качестве функции"),
	ERROR_ENTRY(307, "[Cемантическая] Необъявленный идентификатор"),
	ERROR_ENTRY(308, "[Cемантическая] Попытка переопределения идентификатора"),
	ERROR_ENTRY(309, "[Cемантическая] Функция ничего не возвращает"),
	ERROR_ENTRY(310, "[Cемантическая] Недопустимое значение переменной типа STRING"),
	ERROR_ENTRY(311, "[Cемантическая] Недопустимое значение переменной типа UINT"),
	ERROR_ENTRY(312, "[Cемантическая] Недопустимое значение переменной типа INT"),
	ERROR_ENTRY(313, "[Cемантическая] Недопустимое значение переменной типа UINT"),
	ERROR_ENTRY(314, "[Cемантическая] Недопустимое значение переменной типа CHAR"),
	ERROR_ENTRY(315, "[Cемантическая] Нарушена форма логического выражения"),
	ERROR_ENTRY_NODEF(316),
	ERROR_ENTRY_NODEF(317),
	ERROR_ENTRY_NODEF(318),
	ERROR_ENTRY_NODEF(319),
	ERROR_ENTRY_NODEF10(320),
	ERROR_ENTRY_NODEF10(330),
	ERROR_ENTRY_NODEF10(340),
	ERROR_ENTRY_NODEF10(350),
	ERROR_ENTRY_NODEF10(360),
	ERROR_ENTRY_NODEF10(370),
	ERROR_ENTRY_NODEF10(380),
	ERROR_ENTRY_NODEF10(390),

	ERROR_ENTRY_NODEF100(400),

	ERROR_ENTRY_NODEF100(500),

	ERROR_ENTRY(600,"[Cинтаксическая] Неверная структура программы"),
	ERROR_ENTRY(601,"[Cинтаксическая] Ошибочный оператор"),
	ERROR_ENTRY(602,"[Cинтаксическая] Ошибка в выражении"),
	ERROR_ENTRY(603,"[Cинтаксическая] Ошибка в параметрах функции"),
	ERROR_ENTRY(604,"[Cинтаксическая] Ошибка в параметрах вызываемой функции"),
	ERROR_ENTRY(605,"[Cинтаксическая] Ошибочное определение логического условия"),
	ERROR_ENTRY(606, "[Синтаксическа] Произошла ошибка во время синтаксического анализа"),
	ERROR_ENTRY_NODEF(607),
	ERROR_ENTRY_NODEF(608),
	ERROR_ENTRY_NODEF(609),
	ERROR_ENTRY_NODEF10(610),
	ERROR_ENTRY_NODEF10(620),
	ERROR_ENTRY_NODEF10(630),
	ERROR_ENTRY_NODEF10(640),
	ERROR_ENTRY_NODEF10(650),
	ERROR_ENTRY_NODEF10(660),
	ERROR_ENTRY_NODEF10(670),
	ERROR_ENTRY_NODEF10(680),
	ERROR_ENTRY_NODEF10(690),

	ERROR_ENTRY_NODEF100(700),

	ERROR_ENTRY_NODEF100(800),

	ERROR_ENTRY_NODEF100(900)
};


Error::ERROR Error::geterror(int id)
{
	if ((0 < id) && (id < ERROR_MAX_ENTRY)) {
		return errors[id];
	}
	return errors[0];
}

Error::ERROR Error::geterrorin(int id, int line, int column)
{
	if ((0 < id) && (id < ERROR_MAX_ENTRY)) {
		Error::ERROR* temp = &errors[id];
		temp->place = { (short)line, (short)column };
		return *temp;
	}
	return errors[0];
}

Error::ERROR Error::geterrorword(int id, int line, std::string word) {
	if ((0 < id) && (id < ERROR_MAX_ENTRY)) {
		Error::ERROR* temp = &errors[id];
		temp->word = { (short)line, word };
		return *temp;
	}
	return errors[0];
}
