#include "handler_wrapper.h"
#include "interrupt.h"
#include "memory.h"

void common_handler_er(int);
void common_handler(int);

DO_WRAP(default_handler_0){common_handler(0);}
DO_WRAP(default_handler_1){common_handler(1);}
DO_WRAP(default_handler_2){common_handler(2);}
DO_WRAP(default_handler_3){common_handler(3);}
DO_WRAP(default_handler_4){common_handler(4);}
DO_WRAP(default_handler_5){common_handler(5);}
DO_WRAP(default_handler_6){common_handler(6);}
DO_WRAP(default_handler_7){common_handler(7);}
DO_WRAP(default_handler_8){common_handler(8);}
DO_WRAP(default_handler_9){common_handler(9);}
DO_WRAP(default_handler_10){common_handler(10);}
DO_WRAP(default_handler_11){common_handler(11);}
DO_WRAP(default_handler_12){common_handler(12);}
DO_WRAP(default_handler_13){common_handler(13);}
DO_WRAP(default_handler_14){common_handler(14);}
DO_WRAP(default_handler_15){common_handler(15);}
DO_WRAP(default_handler_16){common_handler(16);}
DO_WRAP(default_handler_17){common_handler(17);}
DO_WRAP(default_handler_18){common_handler(18);}
DO_WRAP(default_handler_19){common_handler(19);}
DO_WRAP(default_handler_20){common_handler(20);}
DO_WRAP(default_handler_21){common_handler(21);}
DO_WRAP(default_handler_22){common_handler(22);}
DO_WRAP(default_handler_23){common_handler(23);}
DO_WRAP(default_handler_24){common_handler(24);}
DO_WRAP(default_handler_25){common_handler(25);}
DO_WRAP(default_handler_26){common_handler(26);}
DO_WRAP(default_handler_27){common_handler(27);}
DO_WRAP(default_handler_28){common_handler(28);}
DO_WRAP(default_handler_29){common_handler(29);}
DO_WRAP(default_handler_30){common_handler(30);}
DO_WRAP(default_handler_31){common_handler(31);}
DO_WRAP(default_handler_32){common_handler(32);}
DO_WRAP(default_handler_33){common_handler(33);}
DO_WRAP(default_handler_34){common_handler(34);}
DO_WRAP(default_handler_35){common_handler(35);}
DO_WRAP(default_handler_36){common_handler(36);}
DO_WRAP(default_handler_37){common_handler(37);}
DO_WRAP(default_handler_38){common_handler(38);}
DO_WRAP(default_handler_39){common_handler(39);}
DO_WRAP(default_handler_40){common_handler(40);}
DO_WRAP(default_handler_41){common_handler(41);}
DO_WRAP(default_handler_42){common_handler(42);}
DO_WRAP(default_handler_43){common_handler(43);}
DO_WRAP(default_handler_44){common_handler(44);}
DO_WRAP(default_handler_45){common_handler(45);}
DO_WRAP(default_handler_46){common_handler(46);}
DO_WRAP(default_handler_47){common_handler(47);}
DO_WRAP(default_handler_48){common_handler(48);}
DO_WRAP(default_handler_49){common_handler(49);}
DO_WRAP(default_handler_50){common_handler(50);}
DO_WRAP(default_handler_51){common_handler(51);}
DO_WRAP(default_handler_52){common_handler(52);}
DO_WRAP(default_handler_53){common_handler(53);}
DO_WRAP(default_handler_54){common_handler(54);}
DO_WRAP(default_handler_55){common_handler(55);}
DO_WRAP(default_handler_56){common_handler(56);}
DO_WRAP(default_handler_57){common_handler(57);}
DO_WRAP(default_handler_58){common_handler(58);}
DO_WRAP(default_handler_59){common_handler(59);}
DO_WRAP(default_handler_60){common_handler(60);}
DO_WRAP(default_handler_61){common_handler(61);}
DO_WRAP(default_handler_62){common_handler(62);}
DO_WRAP(default_handler_63){common_handler(63);}
DO_WRAP(default_handler_64){common_handler(64);}
DO_WRAP(default_handler_65){common_handler(65);}
DO_WRAP(default_handler_66){common_handler(66);}
DO_WRAP(default_handler_67){common_handler(67);}
DO_WRAP(default_handler_68){common_handler(68);}
DO_WRAP(default_handler_69){common_handler(69);}
DO_WRAP(default_handler_70){common_handler(70);}
DO_WRAP(default_handler_71){common_handler(71);}
DO_WRAP(default_handler_72){common_handler(72);}
DO_WRAP(default_handler_73){common_handler(73);}
DO_WRAP(default_handler_74){common_handler(74);}
DO_WRAP(default_handler_75){common_handler(75);}
DO_WRAP(default_handler_76){common_handler(76);}
DO_WRAP(default_handler_77){common_handler(77);}
DO_WRAP(default_handler_78){common_handler(78);}
DO_WRAP(default_handler_79){common_handler(79);}
DO_WRAP(default_handler_80){common_handler(80);}
DO_WRAP(default_handler_81){common_handler(81);}
DO_WRAP(default_handler_82){common_handler(82);}
DO_WRAP(default_handler_83){common_handler(83);}
DO_WRAP(default_handler_84){common_handler(84);}
DO_WRAP(default_handler_85){common_handler(85);}
DO_WRAP(default_handler_86){common_handler(86);}
DO_WRAP(default_handler_87){common_handler(87);}
DO_WRAP(default_handler_88){common_handler(88);}
DO_WRAP(default_handler_89){common_handler(89);}
DO_WRAP(default_handler_90){common_handler(90);}
DO_WRAP(default_handler_91){common_handler(91);}
DO_WRAP(default_handler_92){common_handler(92);}
DO_WRAP(default_handler_93){common_handler(93);}
DO_WRAP(default_handler_94){common_handler(94);}
DO_WRAP(default_handler_95){common_handler(95);}
DO_WRAP(default_handler_96){common_handler(96);}
DO_WRAP(default_handler_97){common_handler(97);}
DO_WRAP(default_handler_98){common_handler(98);}
DO_WRAP(default_handler_99){common_handler(99);}
DO_WRAP(default_handler_100){common_handler(100);}
DO_WRAP(default_handler_101){common_handler(101);}
DO_WRAP(default_handler_102){common_handler(102);}
DO_WRAP(default_handler_103){common_handler(103);}
DO_WRAP(default_handler_104){common_handler(104);}
DO_WRAP(default_handler_105){common_handler(105);}
DO_WRAP(default_handler_106){common_handler(106);}
DO_WRAP(default_handler_107){common_handler(107);}
DO_WRAP(default_handler_108){common_handler(108);}
DO_WRAP(default_handler_109){common_handler(109);}
DO_WRAP(default_handler_110){common_handler(110);}
DO_WRAP(default_handler_111){common_handler(111);}
DO_WRAP(default_handler_112){common_handler(112);}
DO_WRAP(default_handler_113){common_handler(113);}
DO_WRAP(default_handler_114){common_handler(114);}
DO_WRAP(default_handler_115){common_handler(115);}
DO_WRAP(default_handler_116){common_handler(116);}
DO_WRAP(default_handler_117){common_handler(117);}
DO_WRAP(default_handler_118){common_handler(118);}
DO_WRAP(default_handler_119){common_handler(119);}
DO_WRAP(default_handler_120){common_handler(120);}
DO_WRAP(default_handler_121){common_handler(121);}
DO_WRAP(default_handler_122){common_handler(122);}
DO_WRAP(default_handler_123){common_handler(123);}
DO_WRAP(default_handler_124){common_handler(124);}
DO_WRAP(default_handler_125){common_handler(125);}
DO_WRAP(default_handler_126){common_handler(126);}
DO_WRAP(default_handler_127){common_handler(127);}
DO_WRAP(default_handler_128){common_handler(128);}
DO_WRAP(default_handler_129){common_handler(129);}
DO_WRAP(default_handler_130){common_handler(130);}
DO_WRAP(default_handler_131){common_handler(131);}
DO_WRAP(default_handler_132){common_handler(132);}
DO_WRAP(default_handler_133){common_handler(133);}
DO_WRAP(default_handler_134){common_handler(134);}
DO_WRAP(default_handler_135){common_handler(135);}
DO_WRAP(default_handler_136){common_handler(136);}
DO_WRAP(default_handler_137){common_handler(137);}
DO_WRAP(default_handler_138){common_handler(138);}
DO_WRAP(default_handler_139){common_handler(139);}
DO_WRAP(default_handler_140){common_handler(140);}
DO_WRAP(default_handler_141){common_handler(141);}
DO_WRAP(default_handler_142){common_handler(142);}
DO_WRAP(default_handler_143){common_handler(143);}
DO_WRAP(default_handler_144){common_handler(144);}
DO_WRAP(default_handler_145){common_handler(145);}
DO_WRAP(default_handler_146){common_handler(146);}
DO_WRAP(default_handler_147){common_handler(147);}
DO_WRAP(default_handler_148){common_handler(148);}
DO_WRAP(default_handler_149){common_handler(149);}
DO_WRAP(default_handler_150){common_handler(150);}
DO_WRAP(default_handler_151){common_handler(151);}
DO_WRAP(default_handler_152){common_handler(152);}
DO_WRAP(default_handler_153){common_handler(153);}
DO_WRAP(default_handler_154){common_handler(154);}
DO_WRAP(default_handler_155){common_handler(155);}
DO_WRAP(default_handler_156){common_handler(156);}
DO_WRAP(default_handler_157){common_handler(157);}
DO_WRAP(default_handler_158){common_handler(158);}
DO_WRAP(default_handler_159){common_handler(159);}
DO_WRAP(default_handler_160){common_handler(160);}
DO_WRAP(default_handler_161){common_handler(161);}
DO_WRAP(default_handler_162){common_handler(162);}
DO_WRAP(default_handler_163){common_handler(163);}
DO_WRAP(default_handler_164){common_handler(164);}
DO_WRAP(default_handler_165){common_handler(165);}
DO_WRAP(default_handler_166){common_handler(166);}
DO_WRAP(default_handler_167){common_handler(167);}
DO_WRAP(default_handler_168){common_handler(168);}
DO_WRAP(default_handler_169){common_handler(169);}
DO_WRAP(default_handler_170){common_handler(170);}
DO_WRAP(default_handler_171){common_handler(171);}
DO_WRAP(default_handler_172){common_handler(172);}
DO_WRAP(default_handler_173){common_handler(173);}
DO_WRAP(default_handler_174){common_handler(174);}
DO_WRAP(default_handler_175){common_handler(175);}
DO_WRAP(default_handler_176){common_handler(176);}
DO_WRAP(default_handler_177){common_handler(177);}
DO_WRAP(default_handler_178){common_handler(178);}
DO_WRAP(default_handler_179){common_handler(179);}
DO_WRAP(default_handler_180){common_handler(180);}
DO_WRAP(default_handler_181){common_handler(181);}
DO_WRAP(default_handler_182){common_handler(182);}
DO_WRAP(default_handler_183){common_handler(183);}
DO_WRAP(default_handler_184){common_handler(184);}
DO_WRAP(default_handler_185){common_handler(185);}
DO_WRAP(default_handler_186){common_handler(186);}
DO_WRAP(default_handler_187){common_handler(187);}
DO_WRAP(default_handler_188){common_handler(188);}
DO_WRAP(default_handler_189){common_handler(189);}
DO_WRAP(default_handler_190){common_handler(190);}
DO_WRAP(default_handler_191){common_handler(191);}
DO_WRAP(default_handler_192){common_handler(192);}
DO_WRAP(default_handler_193){common_handler(193);}
DO_WRAP(default_handler_194){common_handler(194);}
DO_WRAP(default_handler_195){common_handler(195);}
DO_WRAP(default_handler_196){common_handler(196);}
DO_WRAP(default_handler_197){common_handler(197);}
DO_WRAP(default_handler_198){common_handler(198);}
DO_WRAP(default_handler_199){common_handler(199);}
DO_WRAP(default_handler_200){common_handler(200);}
DO_WRAP(default_handler_201){common_handler(201);}
DO_WRAP(default_handler_202){common_handler(202);}
DO_WRAP(default_handler_203){common_handler(203);}
DO_WRAP(default_handler_204){common_handler(204);}
DO_WRAP(default_handler_205){common_handler(205);}
DO_WRAP(default_handler_206){common_handler(206);}
DO_WRAP(default_handler_207){common_handler(207);}
DO_WRAP(default_handler_208){common_handler(208);}
DO_WRAP(default_handler_209){common_handler(209);}
DO_WRAP(default_handler_210){common_handler(210);}
DO_WRAP(default_handler_211){common_handler(211);}
DO_WRAP(default_handler_212){common_handler(212);}
DO_WRAP(default_handler_213){common_handler(213);}
DO_WRAP(default_handler_214){common_handler(214);}
DO_WRAP(default_handler_215){common_handler(215);}
DO_WRAP(default_handler_216){common_handler(216);}
DO_WRAP(default_handler_217){common_handler(217);}
DO_WRAP(default_handler_218){common_handler(218);}
DO_WRAP(default_handler_219){common_handler(219);}
DO_WRAP(default_handler_220){common_handler(220);}
DO_WRAP(default_handler_221){common_handler(221);}
DO_WRAP(default_handler_222){common_handler(222);}
DO_WRAP(default_handler_223){common_handler(223);}
DO_WRAP(default_handler_224){common_handler(224);}
DO_WRAP(default_handler_225){common_handler(225);}
DO_WRAP(default_handler_226){common_handler(226);}
DO_WRAP(default_handler_227){common_handler(227);}
DO_WRAP(default_handler_228){common_handler(228);}
DO_WRAP(default_handler_229){common_handler(229);}
DO_WRAP(default_handler_230){common_handler(230);}
DO_WRAP(default_handler_231){common_handler(231);}
DO_WRAP(default_handler_232){common_handler(232);}
DO_WRAP(default_handler_233){common_handler(233);}
DO_WRAP(default_handler_234){common_handler(234);}
DO_WRAP(default_handler_235){common_handler(235);}
DO_WRAP(default_handler_236){common_handler(236);}
DO_WRAP(default_handler_237){common_handler(237);}
DO_WRAP(default_handler_238){common_handler(238);}
DO_WRAP(default_handler_239){common_handler(239);}
DO_WRAP(default_handler_240){common_handler(240);}
DO_WRAP(default_handler_241){common_handler(241);}
DO_WRAP(default_handler_242){common_handler(242);}
DO_WRAP(default_handler_243){common_handler(243);}
DO_WRAP(default_handler_244){common_handler(244);}
DO_WRAP(default_handler_245){common_handler(245);}
DO_WRAP(default_handler_246){common_handler(246);}
DO_WRAP(default_handler_247){common_handler(247);}
DO_WRAP(default_handler_248){common_handler(248);}
DO_WRAP(default_handler_249){common_handler(249);}
DO_WRAP(default_handler_250){common_handler(250);}
DO_WRAP(default_handler_251){common_handler(251);}
DO_WRAP(default_handler_252){common_handler(252);}
DO_WRAP(default_handler_253){common_handler(253);}
DO_WRAP(default_handler_254){common_handler(254);}
DO_WRAP(default_handler_255){common_handler(255);}

ER_DO_WRAP(default_handler_er_8){common_handler_er(8);}
ER_DO_WRAP(default_handler_er_10){common_handler_er(10);}
ER_DO_WRAP(default_handler_er_11){common_handler_er(11);}
ER_DO_WRAP(default_handler_er_12){common_handler_er(12);}
ER_DO_WRAP(default_handler_er_13){common_handler_er(13);}
ER_DO_WRAP(default_handler_er_14){common_handler_er(14);}


void interrupt_handler_wrappers_set_defaults() {
	idt_set_gate(0, (uint64_t)&WRAP(default_handler_0), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(1, (uint64_t)&WRAP(default_handler_1), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(2, (uint64_t)&WRAP(default_handler_2), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(3, (uint64_t)&WRAP(default_handler_3), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(4, (uint64_t)&WRAP(default_handler_4), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(5, (uint64_t)&WRAP(default_handler_5), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(6, (uint64_t)&WRAP(default_handler_6), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(7, (uint64_t)&WRAP(default_handler_7), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(8, (uint64_t)&WRAP(default_handler_8), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(9, (uint64_t)&WRAP(default_handler_9), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(10, (uint64_t)&WRAP(default_handler_10), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(11, (uint64_t)&WRAP(default_handler_11), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(12, (uint64_t)&WRAP(default_handler_12), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(13, (uint64_t)&WRAP(default_handler_13), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(14, (uint64_t)&WRAP(default_handler_14), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(15, (uint64_t)&WRAP(default_handler_15), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(16, (uint64_t)&WRAP(default_handler_16), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(17, (uint64_t)&WRAP(default_handler_17), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(18, (uint64_t)&WRAP(default_handler_18), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(19, (uint64_t)&WRAP(default_handler_19), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(20, (uint64_t)&WRAP(default_handler_20), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(21, (uint64_t)&WRAP(default_handler_21), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(22, (uint64_t)&WRAP(default_handler_22), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(23, (uint64_t)&WRAP(default_handler_23), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(24, (uint64_t)&WRAP(default_handler_24), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(25, (uint64_t)&WRAP(default_handler_25), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(26, (uint64_t)&WRAP(default_handler_26), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(27, (uint64_t)&WRAP(default_handler_27), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(28, (uint64_t)&WRAP(default_handler_28), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(29, (uint64_t)&WRAP(default_handler_29), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(30, (uint64_t)&WRAP(default_handler_30), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(31, (uint64_t)&WRAP(default_handler_31), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(32, (uint64_t)&WRAP(default_handler_32), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(33, (uint64_t)&WRAP(default_handler_33), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(34, (uint64_t)&WRAP(default_handler_34), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(35, (uint64_t)&WRAP(default_handler_35), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(36, (uint64_t)&WRAP(default_handler_36), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(37, (uint64_t)&WRAP(default_handler_37), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(38, (uint64_t)&WRAP(default_handler_38), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(39, (uint64_t)&WRAP(default_handler_39), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(40, (uint64_t)&WRAP(default_handler_40), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(41, (uint64_t)&WRAP(default_handler_41), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(42, (uint64_t)&WRAP(default_handler_42), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(43, (uint64_t)&WRAP(default_handler_43), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(44, (uint64_t)&WRAP(default_handler_44), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(45, (uint64_t)&WRAP(default_handler_45), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(46, (uint64_t)&WRAP(default_handler_46), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(47, (uint64_t)&WRAP(default_handler_47), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(48, (uint64_t)&WRAP(default_handler_48), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(49, (uint64_t)&WRAP(default_handler_49), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(50, (uint64_t)&WRAP(default_handler_50), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(51, (uint64_t)&WRAP(default_handler_51), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(52, (uint64_t)&WRAP(default_handler_52), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(53, (uint64_t)&WRAP(default_handler_53), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(54, (uint64_t)&WRAP(default_handler_54), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(55, (uint64_t)&WRAP(default_handler_55), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(56, (uint64_t)&WRAP(default_handler_56), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(57, (uint64_t)&WRAP(default_handler_57), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(58, (uint64_t)&WRAP(default_handler_58), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(59, (uint64_t)&WRAP(default_handler_59), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(60, (uint64_t)&WRAP(default_handler_60), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(61, (uint64_t)&WRAP(default_handler_61), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(62, (uint64_t)&WRAP(default_handler_62), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(63, (uint64_t)&WRAP(default_handler_63), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(64, (uint64_t)&WRAP(default_handler_64), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(65, (uint64_t)&WRAP(default_handler_65), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(66, (uint64_t)&WRAP(default_handler_66), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(67, (uint64_t)&WRAP(default_handler_67), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(68, (uint64_t)&WRAP(default_handler_68), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(69, (uint64_t)&WRAP(default_handler_69), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(70, (uint64_t)&WRAP(default_handler_70), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(71, (uint64_t)&WRAP(default_handler_71), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(72, (uint64_t)&WRAP(default_handler_72), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(73, (uint64_t)&WRAP(default_handler_73), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(74, (uint64_t)&WRAP(default_handler_74), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(75, (uint64_t)&WRAP(default_handler_75), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(76, (uint64_t)&WRAP(default_handler_76), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(77, (uint64_t)&WRAP(default_handler_77), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(78, (uint64_t)&WRAP(default_handler_78), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(79, (uint64_t)&WRAP(default_handler_79), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(80, (uint64_t)&WRAP(default_handler_80), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(81, (uint64_t)&WRAP(default_handler_81), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(82, (uint64_t)&WRAP(default_handler_82), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(83, (uint64_t)&WRAP(default_handler_83), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(84, (uint64_t)&WRAP(default_handler_84), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(85, (uint64_t)&WRAP(default_handler_85), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(86, (uint64_t)&WRAP(default_handler_86), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(87, (uint64_t)&WRAP(default_handler_87), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(88, (uint64_t)&WRAP(default_handler_88), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(89, (uint64_t)&WRAP(default_handler_89), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(90, (uint64_t)&WRAP(default_handler_90), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(91, (uint64_t)&WRAP(default_handler_91), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(92, (uint64_t)&WRAP(default_handler_92), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(93, (uint64_t)&WRAP(default_handler_93), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(94, (uint64_t)&WRAP(default_handler_94), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(95, (uint64_t)&WRAP(default_handler_95), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(96, (uint64_t)&WRAP(default_handler_96), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(97, (uint64_t)&WRAP(default_handler_97), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(98, (uint64_t)&WRAP(default_handler_98), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(99, (uint64_t)&WRAP(default_handler_99), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(100, (uint64_t)&WRAP(default_handler_100), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(101, (uint64_t)&WRAP(default_handler_101), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(102, (uint64_t)&WRAP(default_handler_102), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(103, (uint64_t)&WRAP(default_handler_103), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(104, (uint64_t)&WRAP(default_handler_104), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(105, (uint64_t)&WRAP(default_handler_105), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(106, (uint64_t)&WRAP(default_handler_106), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(107, (uint64_t)&WRAP(default_handler_107), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(108, (uint64_t)&WRAP(default_handler_108), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(109, (uint64_t)&WRAP(default_handler_109), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(110, (uint64_t)&WRAP(default_handler_110), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(111, (uint64_t)&WRAP(default_handler_111), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(112, (uint64_t)&WRAP(default_handler_112), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(113, (uint64_t)&WRAP(default_handler_113), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(114, (uint64_t)&WRAP(default_handler_114), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(115, (uint64_t)&WRAP(default_handler_115), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(116, (uint64_t)&WRAP(default_handler_116), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(117, (uint64_t)&WRAP(default_handler_117), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(118, (uint64_t)&WRAP(default_handler_118), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(119, (uint64_t)&WRAP(default_handler_119), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(120, (uint64_t)&WRAP(default_handler_120), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(121, (uint64_t)&WRAP(default_handler_121), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(122, (uint64_t)&WRAP(default_handler_122), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(123, (uint64_t)&WRAP(default_handler_123), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(124, (uint64_t)&WRAP(default_handler_124), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(125, (uint64_t)&WRAP(default_handler_125), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(126, (uint64_t)&WRAP(default_handler_126), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(127, (uint64_t)&WRAP(default_handler_127), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(128, (uint64_t)&WRAP(default_handler_128), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(129, (uint64_t)&WRAP(default_handler_129), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(130, (uint64_t)&WRAP(default_handler_130), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(131, (uint64_t)&WRAP(default_handler_131), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(132, (uint64_t)&WRAP(default_handler_132), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(133, (uint64_t)&WRAP(default_handler_133), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(134, (uint64_t)&WRAP(default_handler_134), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(135, (uint64_t)&WRAP(default_handler_135), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(136, (uint64_t)&WRAP(default_handler_136), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(137, (uint64_t)&WRAP(default_handler_137), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(138, (uint64_t)&WRAP(default_handler_138), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(139, (uint64_t)&WRAP(default_handler_139), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(140, (uint64_t)&WRAP(default_handler_140), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(141, (uint64_t)&WRAP(default_handler_141), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(142, (uint64_t)&WRAP(default_handler_142), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(143, (uint64_t)&WRAP(default_handler_143), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(144, (uint64_t)&WRAP(default_handler_144), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(145, (uint64_t)&WRAP(default_handler_145), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(146, (uint64_t)&WRAP(default_handler_146), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(147, (uint64_t)&WRAP(default_handler_147), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(148, (uint64_t)&WRAP(default_handler_148), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(149, (uint64_t)&WRAP(default_handler_149), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(150, (uint64_t)&WRAP(default_handler_150), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(151, (uint64_t)&WRAP(default_handler_151), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(152, (uint64_t)&WRAP(default_handler_152), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(153, (uint64_t)&WRAP(default_handler_153), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(154, (uint64_t)&WRAP(default_handler_154), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(155, (uint64_t)&WRAP(default_handler_155), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(156, (uint64_t)&WRAP(default_handler_156), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(157, (uint64_t)&WRAP(default_handler_157), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(158, (uint64_t)&WRAP(default_handler_158), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(159, (uint64_t)&WRAP(default_handler_159), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(160, (uint64_t)&WRAP(default_handler_160), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(161, (uint64_t)&WRAP(default_handler_161), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(162, (uint64_t)&WRAP(default_handler_162), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(163, (uint64_t)&WRAP(default_handler_163), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(164, (uint64_t)&WRAP(default_handler_164), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(165, (uint64_t)&WRAP(default_handler_165), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(166, (uint64_t)&WRAP(default_handler_166), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(167, (uint64_t)&WRAP(default_handler_167), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(168, (uint64_t)&WRAP(default_handler_168), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(169, (uint64_t)&WRAP(default_handler_169), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(170, (uint64_t)&WRAP(default_handler_170), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(171, (uint64_t)&WRAP(default_handler_171), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(172, (uint64_t)&WRAP(default_handler_172), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(173, (uint64_t)&WRAP(default_handler_173), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(174, (uint64_t)&WRAP(default_handler_174), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(175, (uint64_t)&WRAP(default_handler_175), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(176, (uint64_t)&WRAP(default_handler_176), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(177, (uint64_t)&WRAP(default_handler_177), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(178, (uint64_t)&WRAP(default_handler_178), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(179, (uint64_t)&WRAP(default_handler_179), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(180, (uint64_t)&WRAP(default_handler_180), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(181, (uint64_t)&WRAP(default_handler_181), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(182, (uint64_t)&WRAP(default_handler_182), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(183, (uint64_t)&WRAP(default_handler_183), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(184, (uint64_t)&WRAP(default_handler_184), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(185, (uint64_t)&WRAP(default_handler_185), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(186, (uint64_t)&WRAP(default_handler_186), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(187, (uint64_t)&WRAP(default_handler_187), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(188, (uint64_t)&WRAP(default_handler_188), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(189, (uint64_t)&WRAP(default_handler_189), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(190, (uint64_t)&WRAP(default_handler_190), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(191, (uint64_t)&WRAP(default_handler_191), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(192, (uint64_t)&WRAP(default_handler_192), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(193, (uint64_t)&WRAP(default_handler_193), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(194, (uint64_t)&WRAP(default_handler_194), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(195, (uint64_t)&WRAP(default_handler_195), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(196, (uint64_t)&WRAP(default_handler_196), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(197, (uint64_t)&WRAP(default_handler_197), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(198, (uint64_t)&WRAP(default_handler_198), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(199, (uint64_t)&WRAP(default_handler_199), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(200, (uint64_t)&WRAP(default_handler_200), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(201, (uint64_t)&WRAP(default_handler_201), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(202, (uint64_t)&WRAP(default_handler_202), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(203, (uint64_t)&WRAP(default_handler_203), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(204, (uint64_t)&WRAP(default_handler_204), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(205, (uint64_t)&WRAP(default_handler_205), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(206, (uint64_t)&WRAP(default_handler_206), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(207, (uint64_t)&WRAP(default_handler_207), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(208, (uint64_t)&WRAP(default_handler_208), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(209, (uint64_t)&WRAP(default_handler_209), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(210, (uint64_t)&WRAP(default_handler_210), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(211, (uint64_t)&WRAP(default_handler_211), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(212, (uint64_t)&WRAP(default_handler_212), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(213, (uint64_t)&WRAP(default_handler_213), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(214, (uint64_t)&WRAP(default_handler_214), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(215, (uint64_t)&WRAP(default_handler_215), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(216, (uint64_t)&WRAP(default_handler_216), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(217, (uint64_t)&WRAP(default_handler_217), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(218, (uint64_t)&WRAP(default_handler_218), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(219, (uint64_t)&WRAP(default_handler_219), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(220, (uint64_t)&WRAP(default_handler_220), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(221, (uint64_t)&WRAP(default_handler_221), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(222, (uint64_t)&WRAP(default_handler_222), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(223, (uint64_t)&WRAP(default_handler_223), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(224, (uint64_t)&WRAP(default_handler_224), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(225, (uint64_t)&WRAP(default_handler_225), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(226, (uint64_t)&WRAP(default_handler_226), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(227, (uint64_t)&WRAP(default_handler_227), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(228, (uint64_t)&WRAP(default_handler_228), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(229, (uint64_t)&WRAP(default_handler_229), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(230, (uint64_t)&WRAP(default_handler_230), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(231, (uint64_t)&WRAP(default_handler_231), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(232, (uint64_t)&WRAP(default_handler_232), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(233, (uint64_t)&WRAP(default_handler_233), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(234, (uint64_t)&WRAP(default_handler_234), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(235, (uint64_t)&WRAP(default_handler_235), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(236, (uint64_t)&WRAP(default_handler_236), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(237, (uint64_t)&WRAP(default_handler_237), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(238, (uint64_t)&WRAP(default_handler_238), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(239, (uint64_t)&WRAP(default_handler_239), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(240, (uint64_t)&WRAP(default_handler_240), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(241, (uint64_t)&WRAP(default_handler_241), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(242, (uint64_t)&WRAP(default_handler_242), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(243, (uint64_t)&WRAP(default_handler_243), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(244, (uint64_t)&WRAP(default_handler_244), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(245, (uint64_t)&WRAP(default_handler_245), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(246, (uint64_t)&WRAP(default_handler_246), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(247, (uint64_t)&WRAP(default_handler_247), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(248, (uint64_t)&WRAP(default_handler_248), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(249, (uint64_t)&WRAP(default_handler_249), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(250, (uint64_t)&WRAP(default_handler_250), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(251, (uint64_t)&WRAP(default_handler_251), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(252, (uint64_t)&WRAP(default_handler_252), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(253, (uint64_t)&WRAP(default_handler_253), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(254, (uint64_t)&WRAP(default_handler_254), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(255, (uint64_t)&WRAP(default_handler_255), KERNEL_CODE, INTGATE_TYPE);

	idt_set_gate(8, (uint64_t)&WRAP(default_handler_er_8), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(10, (uint64_t)&WRAP(default_handler_er_10), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(11, (uint64_t)&WRAP(default_handler_er_11), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(12, (uint64_t)&WRAP(default_handler_er_12), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(13, (uint64_t)&WRAP(default_handler_er_13), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(14, (uint64_t)&WRAP(default_handler_er_14), KERNEL_CODE, INTGATE_TYPE);
}
