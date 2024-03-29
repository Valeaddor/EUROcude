##################
Эксплуатация IOOT-PRO
##################

.. contents:: Содержание
   :depth: 3

Общие указания
==============

Вид оборудования, для которого составлена инструкция
----------------------------------------------------

Контроллеры IOOT-PRO — это модульный масштабируемый контроллер для автоматизации технологических процессов и зданий.


Наименование функций АС, реализуемых на данном оборудовании
-----------------------------------------------------------

IOOT-PRO имеет следующие функциональные возможности:
 - программирование и настройка посредством Siemens TIA Portal или PromUC RuleEngine, в том числе удалённо;
 - до 32 входов/выходов различных типов (дискретные, аналоговые, 24/220 В, датчики температуры NTC10k или PT1000, и т.д.);
 - возможность последовательного включения по Ethernet;
 - поддержка MQTT, Modbus, Profinet, BACnet.



Регламент и режимы работы оборудования по реализации функций
------------------------------------------------------------

IOOT-PRO обеспечивают свое функционирование в перечисленных ниже режимах:
 - штатный (нормальный) режим. Компоненты всех уровней системы исправны и функционируют. Каналы связи работают с предусмотренными характеристиками;
 - пусковой режим. Режим требует первоначальной настройки устройтсва;
 - аварийный режим.

Более подробная информация по режимам представлена в документах «Пояснительная записка к техническому проекту»


Перечень эксплуатационных документов, которыми должен дополнительно руководствоваться персонал при эксплуатации данного оборудования
------------------------------------------------------------------------------------------------------------------------------------

Перечень эксплуатационных документов:
 - **«Руководство пользователя IOOT-PRO»**;
 - **«Руководство пользователя SCADA PromUC»**.


Меры безопасности
=================

Электрическая безопасность
--------------------------

Для обеспечения защиты от случайного соприкосновения
с соединениями при напряжении свыше 42В, устройство
должно быть установлено внутри корпуса или шкафа.
Корпус должен открываться только с помощью ключа или
иного инструмента.

Кабели AC 230 В должны иметь двойную изоляцию от
кабелей малого по условиям безопасности напряжения.


Утилизация
----------

Устройтсво содержит электрические компоненты и должно быть утилизирован отдельно от бытовых отходов,
в соответствии с местным действующим законодательством!


Порядок работы
==============

Состав и квалификация персонала, допускаемого к эксплуатации оборудования
-------------------------------------------------------------------------

- Первоначальная установка и настройка устройства (ПНР):
   Инженер

- Эксплуатация:
   Инженер

Персонал, обслуживающий устройство, должен быть подготовлен к выполнению
своих обязанностей в соответствии с **«Должностными инструкциями»** и **«Руководством
пользователя IOOT-PRO»**.


Порядок проверки знаний персонала и допуска его к работе
--------------------------------------------------------

Персонал получает допуск к работе после проверки знаний по соответствующим должностным инструкциям,
а также после изучения документов **«Руководство пользователя IOOT-PRO»** и **«Руководство пользователя SCADA PromUC»**.
Допуск к работе выдаёт руководитель соответствующего подразделения, обслуживающего устройства.
Описание работ и последовательность их выполнения указаны в должностных инструкциях персонала.


Описание работ и последовательность их выполнения
-------------------------------------------------

Установка и настройка устройства описана в **«Руководство пользователя IOOT-PRO»**.



Проверка правильности функционирования
======================================

Содержание и методики основных проверок работоспособности оборудования и
правильности выполнения функций системы указаны в документе **«Программа и методика
испытаний»**



Указания о действиях в разных режимах
=====================================

- штатный (нормальный) режим.
   действия персонала описаны в **«Руководство пользователя SCADA PromUC»**;
- пусковой режим.
   действия персонала описаны в **«Руководство пользователя IOOT-PRO»**;
- аварийный режим.
   действия персонала описаны в **«Руководство пользователя IOOT-PRO»**.
