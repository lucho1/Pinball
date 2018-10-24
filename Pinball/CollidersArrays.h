#ifndef _COLLIDERSARRAYS_H_
#define _COLLIDERSARRAYS_H_

#define INT_PIVOT_X 0
#define INT_PIVOT_Y 0
#define FLOAT_PIVOT_X 0.00000f
#define FLOAT_PIVOT_Y 0.00000f

template<typename T>
////template argument deduction

int GetArraySize(T&arr1) { //Passing the array by reference 

	return sizeof(arr1) / sizeof(arr1[0]); //Correctly returns the size of 'arr1'
}

//Example For Collider
int points[38] = {
	70, 666,
	80, 637,
	94, 617,
	114, 599,
	135, 584,
	162, 572,
	192, 568,
	234, 573,
	265, 579,
	287, 589,
	306, 607,
	314, 625,
	319, 639,
	321, 664,
	346, 526,
	177, 457,
	100, 524,
	63, 587,
	45, 629
};

//MONSTER COLLIDERS
int Monster[194] = {
	177, 765,
	191, 788,
	197, 797,
	201, 801,
	206, 802,
	210, 800,
	210, 795,
	209, 786,
	207, 770,
	208, 757,
	210, 740,
	214, 725,
	222, 700,
	236, 666,
	254, 633,
	281, 586,
	292, 572,
	300, 562,
	307, 555,
	317, 549,
	324, 546,
	330, 544,
	338, 543,
	344, 543,
	351, 544,
	357, 547,
	371, 558,
	376, 563,
	382, 572,
	386, 577,
	404, 599,
	429, 624,
	464, 657,
	497, 691,
	518, 715,
	528, 730,
	532, 736,
	536, 742,
	539, 748,
	545, 762,
	548, 773,
	551, 783,
	553, 793,
	553, 796,
	554, 800,
	558, 802,
	561, 801,
	563, 799,
	566, 792,
	569, 782,
	571, 776,
	573, 769,
	573, 749,
	572, 742,
	565, 718,
	555, 692,
	534, 660,
	511, 630,
	497, 613,
	473, 589,
	457, 574,
	448, 564,
	442, 555,
	439, 546,
	437, 539,
	435, 499,
	435, 351,
	433, 311,
	406, 296,
	381, 298,
	371, 319,
	365, 331,
	358, 342,
	344, 363,
	334, 377,
	327, 388,
	313, 406,
	304, 418,
	281, 448,
	270, 464,
	263, 473,
	253, 489,
	229, 532,
	186, 611,
	177, 630,
	173, 639,
	169, 649,
	165, 660,
	163, 671,
	161, 680,
	160, 693,
	160, 706,
	161, 719,
	162, 730,
	165, 741,
	172, 755,
	175, 761
};

//RED COLLIDERS
int RightRed[42] = {
	866, 1297,
	866, 1285,
	866, 1278,
	865, 1274,
	863, 1271,
	859, 1270,
	855, 1270,
	852, 1271,
	849, 1274,
	824, 1303,
	765, 1443,
	743, 1493,
	743, 1497,
	744, 1501,
	763, 1521,
	766, 1523,
	771, 1523,
	860, 1488,
	863, 1486,
	866, 1484,
	866, 1326
};
int LeftRed[42] = {
	187, 1275,
	183, 1271,
	180, 1270,
	176, 1270,
	172, 1271,
	169, 1273,
	168, 1277,
	168, 1280,
	168, 1480,
	169, 1483,
	171, 1485,
	174, 1487,
	263, 1523,
	269, 1523,
	272, 1521,
	290, 1502,
	292, 1499,
	292, 1495,
	210, 1303,
	209, 1301,
	192, 1280
};

//LO METALICO DEL MONTSTRUO
int MonsterMetalic[50] = {
	283, 769,
	449, 769,
	452, 768,
	455, 766,
	458, 764,
	461, 760,
	463, 757,
	463, 753,
	463, 747,
	462, 743,
	460, 738,
	373, 643,
	364, 638,
	355, 635,
	343, 634,
	334, 636,
	326, 640,
	321, 644,
	317, 648,
	310, 658,
	292, 698,
	279, 735,
	279, 758,
	279, 764,
	280, 767
};

//UFO BUTTON
int UfoButton[22] = {
	336, 770,
	285, 770,
	285, 806,
	286, 810,
	288, 813,
	291, 815,
	327, 815,
	331, 814,
	334, 811,
	336, 806,
	336, 773
};

//JACKPOT
int Jackpot[70] = {
	277, 184,
	322, 196,
	325, 198,
	327, 201,
	327, 273,
	264, 362,
	223, 416,
	209, 436,
	197, 454,
	182, 478,
	166, 510,
	154, 538,
	142, 570,
	140, 573,
	136, 574,
	131, 572,
	124, 559,
	114, 534,
	105, 504,
	101, 488,
	99, 471,
	99, 448,
	101, 430,
	106, 407,
	112, 391,
	120, 372,
	129, 352,
	144, 325,
	165, 295,
	186, 268,
	202, 250,
	231, 221,
	260, 194,
	268, 188,
	273, 185
};

//PILL COLLIDER
int Pill[60] = {
	544, 271,
	544, 260,
	543, 255,
	541, 251,
	538, 247,
	534, 243,
	529, 240,
	525, 239,
	510, 239,
	506, 240,
	502, 242,
	498, 245,
	494, 249,
	491, 256,
	490, 260,
	490, 328,
	491, 333,
	494, 337,
	498, 341,
	501, 344,
	507, 347,
	511, 348,
	522, 348,
	526, 347,
	531, 345,
	534, 343,
	537, 340,
	541, 336,
	544, 331,
	544, 280
};

//ARROW COLLIDER
int Arrow[30] = {
	484, 829,
	484, 856,
	512, 856,
	512, 820,
	522, 820,
	523, 819,
	523, 817,
	501, 785,
	499, 784,
	498, 784,
	496, 785,
	473, 817,
	473, 819,
	475, 820,
	484, 820
};

//ROUNDED SQUARE
int RoundedSquare[26] = {
	966, 818,
	941, 818,
	937, 820,
	935, 822,
	935, 861,
	937, 863,
	940, 864,
	988, 864,
	992, 863,
	994, 860,
	994, 824,
	992, 820,
	989, 818
};

//HOLDERS
int HolderLeft[58] = {
	99, 1347,
	101, 1345,
	104, 1341,
	104, 1335,
	102, 1329,
	99, 1324,
	94, 1323,
	87, 1323,
	83, 1325,
	80, 1328,
	78, 1331,
	78, 1336,
	78, 1339,
	79, 1342,
	81, 1345,
	81, 1361,
	80, 1532,
	81, 1536,
	83, 1539,
	90, 1542,
	153, 1574,
	303, 1649,
	322, 1630,
	328, 1611,
	317, 1604,
	194, 1555,
	100, 1518,
	100, 1449,
	99, 1355
};
int HolderRight[46] = {
	947, 1340,
	951, 1334,
	951, 1328,
	949, 1322,
	945, 1319,
	941, 1317,
	933, 1317,
	930, 1319,
	926, 1322,
	924, 1328,
	925, 1336,
	929, 1341,
	929, 1512,
	679, 1608,
	667, 1641,
	700, 1647,
	706, 1648,
	892, 1559,
	943, 1535,
	947, 1532,
	949, 1528,
	948, 1458,
	947, 1349
};

//WALLS
int WallRight[168] = { //Careful with these 2, IDK if name is OK
	663, 1836,
	663, 1773,
	664, 1770,
	684, 1760,
	878, 1669,
	972, 1625,
	976, 1622,
	980, 1619,
	983, 1615,
	986, 1611,
	989, 1605,
	992, 1598,
	994, 1591,
	996, 1581,
	996, 1574,
	997, 1299,
	997, 1296,
	995, 1293,
	967, 1265,
	923, 1219,
	895, 1187,
	892, 1183,
	889, 1178,
	886, 1173,
	884, 1168,
	884, 907,
	887, 886,
	889, 876,
	894, 861,
	899, 845,
	905, 828,
	914, 804,
	924, 779,
	934, 751,
	965, 670,
	980, 632,
	953, 563,
	853, 781,
	848, 788,
	837, 788,
	828, 787,
	820, 781,
	814, 773,
	812, 765,
	812, 757,
	819, 739,
	880, 609,
	936, 494,
	890, 292,
	837, 292,
	830, 290,
	825, 287,
	821, 284,
	818, 277,
	818, 204,
	820, 197,
	824, 192,
	830, 188,
	837, 187,
	846, 187,
	855, 188,
	890, 215,
	912, 236,
	923, 248,
	942, 277,
	969, 320,
	987, 360,
	996, 388,
	1002, 415,
	1008, 445,
	1012, 473,
	1015, 514,
	1015, 564,
	1015, 612,
	1015, 700,
	1015, 887,
	1015, 1102,
	1015, 1332,
	1015, 1547,
	1016, 1700,
	1016, 1818,
	775, 1818,
	696, 1833,
	680, 1836
};
int WallLeft[128] = {
	250, 1815,
	327, 1836,
	327, 1777,
	39, 1640,
	30, 1631,
	27, 1623,
	26, 1609,
	24, 1314,
	100, 1241,
	100, 1209,
	30, 1140,
	30, 769,
	30, 491,
	31, 472,
	35, 447,
	43, 410,
	56, 360,
	73, 318,
	91, 286,
	107, 263,
	140, 224,
	181, 183,
	235, 137,
	268, 112,
	294, 96,
	325, 78,
	361, 62,
	395, 50,
	440, 38,
	483, 30,
	521, 25,
	575, 23,
	635, 27,
	686, 32,
	729, 43,
	763, 53,
	784, 61,
	813, 73,
	840, 89,
	862, 103,
	890, 126,
	943, 177,
	986, 231,
	1009, 264,
	1035, 315,
	1047, 349,
	1059, 394,
	1067, 456,
	1070, 515,
	1070, 565,
	1070, 878,
	1070, 1280,
	1070, 1675,
	1070, 1810,
	1096, 1831,
	1098, 107,
	882, 27,
	687, 8,
	326, 15,
	16, 196,
	6, 438,
	6, 1223,
	5, 1825,
	212, 1826
};

//FLICKERS
int FlickerRight[60] = {
	669, 1609,
	677, 1607,
	685, 1607,
	692, 1609,
	698, 1612,
	702, 1617,
	705, 1621,
	707, 1625,
	708, 1630,
	708, 1636,
	707, 1641,
	706, 1645,
	704, 1650,
	701, 1654,
	698, 1657,
	694, 1659,
	560, 1707,
	555, 1708,
	551, 1708,
	547, 1706,
	542, 1703,
	539, 1700,
	537, 1696,
	536, 1691,
	537, 1686,
	539, 1682,
	542, 1678,
	546, 1674,
	553, 1670,
	665, 1611
};
int FlickerLeft[56] = {
	335, 1608,
	328, 1607,
	322, 1607,
	317, 1609,
	310, 1612,
	306, 1617,
	301, 1622,
	299, 1628,
	298, 1633,
	299, 1639,
	300, 1644,
	302, 1649,
	306, 1654,
	311, 1657,
	317, 1660,
	444, 1707,
	448, 1708,
	453, 1709,
	457, 1708,
	461, 1707,
	465, 1704,
	470, 1697,
	471, 1692,
	470, 1685,
	468, 1680,
	463, 1675,
	451, 1669,
	339, 1610
};
#endif