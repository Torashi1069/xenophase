#include "Protocol.h"
#include "packet/all.h"


static ProtocolImpl ProtocolInstance("Client 2013-10-22a Ragexe France");
void ProtocolImpl::InitInstance()
{
	REGN(100, 55, HEADER_CA_LOGIN, PROTOID_CA_LOGIN, PACKET_CA_LOGIN);
	REGN(101, 17, HEADER_CH_ENTER, PROTOID_CH_ENTER, PACKET_CH_ENTER);
	REGN(102, 3, HEADER_CH_SELECT_CHAR, PROTOID_CH_SELECT_CHAR, PACKET_CH_SELECT_CHAR);
	REGN(103, 37, HEADER_CH_MAKE_CHAR, PROTOID_CH_MAKE_CHAR, PACKET_CH_MAKE_CHAR);
	REGN(104, 46, HEADER_CH_DELETE_CHAR, PROTOID_CH_DELETE_CHAR, PACKET_CH_DELETE_CHAR);
	REGV(105, 47, HEADER_AC_ACCEPT_LOGIN, PROTOID_AC_ACCEPT_LOGIN, PACKET_AC_ACCEPT_LOGIN);
	REGN(106, 23, HEADER_AC_REFUSE_LOGIN, PROTOID_AC_REFUSE_LOGIN, PACKET_AC_REFUSE_LOGIN);
	REGN(0x7FFF, 4, HEADER_HC_AID_RAW, PROTOID_HC_AID, PACKET_HC_AID_RAW);
//	REGV(107, 7, HEADER_HC_ACCEPT_ENTER, PROTOID_HC_ACCEPT_ENTER, PACKET_HC_ACCEPT_ENTER_THAI20130312); // broken
	REGN(108, 3, HEADER_HC_REFUSE_ENTER, PROTOID_HC_REFUSE_ENTER, PACKET_HC_REFUSE_ENTER);
	REGN(109, 118, HEADER_HC_ACCEPT_MAKECHAR, PROTOID_HC_ACCEPT_MAKECHAR, PACKET_HC_ACCEPT_MAKECHAR_THAI20130312);
	REGN(110, 3, HEADER_HC_REFUSE_MAKECHAR, PROTOID_HC_REFUSE_MAKECHAR, PACKET_HC_REFUSE_MAKECHAR);
	REGN(111, 2, HEADER_HC_ACCEPT_DELETECHAR, PROTOID_HC_ACCEPT_DELETECHAR, PACKET_HC_ACCEPT_DELETECHAR);
	REGN(112, 3, HEADER_HC_REFUSE_DELETECHAR, PROTOID_HC_REFUSE_DELETECHAR, PACKET_HC_REFUSE_DELETECHAR);
	REGN(113, 28, HEADER_HC_NOTIFY_ZONESVR, PROTOID_HC_NOTIFY_ZONESVR, PACKET_HC_NOTIFY_ZONESVR);
	REGN(114, 19, HEADER_CZ_ENTER, PROTOID_CZ_ENTER, PACKET_CZ_ENTER);
//	REGN(0x7FFE, 4, HEADER_ZC_AID_RAW, PROTOID_ZC_AID, PACKET_ZC_AID_RAW);
	REGN(115, 11, HEADER_ZC_ACCEPT_ENTER, PROTOID_ZC_ACCEPT_ENTER, PACKET_ZC_ACCEPT_ENTER);
	REGN(116, 3, HEADER_ZC_REFUSE_ENTER, PROTOID_ZC_REFUSE_ENTER, PACKET_ZC_REFUSE_ENTER);
	REGV(117, 11);
	REGN(118, 9);
	REGN(119, 5);
	REGN(120, 55);
	REGN(121, 53);
	REGN(122, 58);
	REGN(123, 60);
	REGN(124, 44);
	REGN(125, 2, HEADER_CZ_NOTIFY_ACTORINIT, PROTOID_CZ_NOTIFY_ACTORINIT, PACKET_CZ_NOTIFY_ACTORINIT);
	REGN(126, 6, HEADER_CZ_REQUEST_TIME); //TODO
	REGN(127, 6, HEADER_ZC_NOTIFY_TIME, PROTOID_ZC_NOTIFY_TIME, PACKET_ZC_NOTIFY_TIME);
	REGN(128, 7, HEADER_ZC_NOTIFY_VANISH, PROTOID_ZC_NOTIFY_VANISH, PACKET_ZC_NOTIFY_VANISH);
	REGN(129, 3, HEADER_SC_NOTIFY_BAN, PROTOID_SC_NOTIFY_BAN, PACKET_SC_NOTIFY_BAN);
	REGN(130, 2);
	REGN(131, 2);
	REGN(132, 2);
	REGN(133, 5);
	REGN(134, 16);
	REGN(135, 12, HEADER_ZC_NOTIFY_PLAYERMOVE, PROTOID_ZC_NOTIFY_PLAYERMOVE, PACKET_ZC_NOTIFY_PLAYERMOVE);
	REGN(136, 10, HEADER_ZC_STOPMOVE, PROTOID_ZC_STOPMOVE, PACKET_ZC_STOPMOVE);
	REGN(137, 7, HEADER_CZ_REQUEST_ACT, PROTOID_CZ_REQUEST_ACT, PACKET_CZ_REQUEST_ACT);
	REGN(138, 29, HEADER_ZC_NOTIFY_ACT, PROTOID_ZC_NOTIFY_ACT, PACKET_ZC_NOTIFY_ACT);
	REGN(139, 23);
	REGV(140, 4, HEADER_CZ_REQUEST_CHAT, PROTOID_CZ_REQUEST_CHAT, PACKET_CZ_REQUEST_CHAT);
	REGV(141, 8, HEADER_ZC_NOTIFY_CHAT, PROTOID_ZC_NOTIFY_CHAT, PACKET_ZC_NOTIFY_CHAT);
	REGV(142, 4, HEADER_ZC_NOTIFY_PLAYERCHAT, PROTOID_ZC_NOTIFY_PLAYERCHAT, PACKET_ZC_NOTIFY_PLAYERCHAT);
//	REGN(143, 6, HEADER_SC_ENTRY_ACK, PROTOID_SC_ENTRY_ACK, PACKET_SC_ENTRY_ACK); // no-len
	REGN(144, 7, HEADER_CZ_CONTACTNPC, PROTOID_CZ_CONTACTNPC, PACKET_CZ_CONTACTNPC);
	REGN(145, 22, HEADER_ZC_NPCACK_MAPMOVE, PROTOID_ZC_NPCACK_MAPMOVE, PACKET_ZC_NPCACK_MAPMOVE);
	REGN(146, 28);
	REGN(147, 2);
	REGN(148, 6, HEADER_CZ_REQNAME, PROTOID_CZ_REQNAME, PACKET_CZ_REQNAME);
	REGN(149, 30, HEADER_ZC_ACK_REQNAME, PROTOID_ZC_ACK_REQNAME, PACKET_ZC_ACK_REQNAME);
	REGV(150, 28);
	REGV(151, 32);
	REGN(152, 3);
	REGV(153, 4);
	REGV(154, 4);
	REGN(155, 5, HEADER_CZ_CHANGE_DIRECTION, PROTOID_CZ_CHANGE_DIRECTION, PACKET_CZ_CHANGE_DIRECTION);
	REGN(156, 9, HEADER_ZC_CHANGE_DIRECTION, PROTOID_ZC_CHANGE_DIRECTION, PACKET_ZC_CHANGE_DIRECTION);
	REGN(157, 17);
	REGN(158, 17);
	REGN(159, 6);
	REGN(160, 23, HEADER_ZC_ITEM_PICKUP_ACK, PROTOID_ZC_ITEM_PICKUP_ACK, PACKET_ZC_ITEM_PICKUP_ACK);
	REGN(161, 6);
	REGN(162, 6);
	REGV(163, 4, HEADER_ZC_NORMAL_ITEMLIST, PROTOID_ZC_NORMAL_ITEMLIST, PACKET_ZC_NORMAL_ITEMLIST);
	REGV(164, 4, HEADER_ZC_EQUIPMENT_ITEMLIST, PROTOID_ZC_EQUIPMENT_ITEMLIST, PACKET_ZC_EQUIPMENT_ITEMLIST);
	REGV(165, 4);
	REGV(166, 4);
	REGN(167, 8);
	REGN(168, 7, HEADER_ZC_USE_ITEM_ACK, PROTOID_ZC_USE_ITEM_ACK, PACKET_ZC_USE_ITEM_ACK);
	REGN(169, 6);
	REGN(170, 9);
	REGN(171, 4);
	REGN(172, 7);
//	REGN(173, 4, HEADER_CZ_REQ_ITEM_EXPLANATION_BYNAME, PROTOID_CZ_REQ_ITEM_EXPLANATION_BYNAME, PACKET_CZ_REQ_ITEM_EXPLANATION_BYNAME); // no-len
//	REGV(174, 4, HEADER_ZC_REQ_ITEM_EXPLANATION_ACK, PROTOID_ZC_REQ_ITEM_EXPLANATION_ACK, PACKET_ZC_REQ_ITEM_EXPLANATION_ACK);
	REGN(175, 6, HEADER_ZC_ITEM_THROW_ACK, PROTOID_ZC_ITEM_THROW_ACK, PACKET_ZC_ITEM_THROW_ACK);
	REGN(176, 8, HEADER_ZC_PAR_CHANGE, PROTOID_ZC_PAR_CHANGE, PACKET_ZC_PAR_CHANGE);
	REGN(177, 8, HEADER_ZC_LONGPAR_CHANGE, PROTOID_ZC_LONGPAR_CHANGE, PACKET_ZC_LONGPAR_CHANGE);
	REGN(178, 3, HEADER_CZ_RESTART, PROTOID_CZ_RESTART, PACKET_CZ_RESTART);
	REGN(179, 3, HEADER_ZC_RESTART_ACK, PROTOID_ZC_RESTART_ACK, PACKET_ZC_RESTART_ACK);
	REGV(180, 8, HEADER_ZC_SAY_DIALOG, PROTOID_ZC_SAY_DIALOG, PACKET_ZC_SAY_DIALOG);
	REGN(181, 6, HEADER_ZC_WAIT_DIALOG, PROTOID_ZC_WAIT_DIALOG, PACKET_ZC_WAIT_DIALOG);
	REGN(182, 6, HEADER_ZC_CLOSE_DIALOG, PROTOID_ZC_CLOSE_DIALOG, PACKET_ZC_CLOSE_DIALOG);
	REGV(183, 8, HEADER_ZC_MENU_LIST, PROTOID_ZC_MENU_LIST, PACKET_ZC_MENU_LIST);
	REGN(184, 7, HEADER_CZ_CHOOSE_MENU, PROTOID_CZ_CHOOSE_MENU, PACKET_CZ_CHOOSE_MENU);
	REGN(185, 6, HEADER_CZ_REQ_NEXT_SCRIPT, PROTOID_CZ_REQ_NEXT_SCRIPT, PACKET_CZ_REQ_NEXT_SCRIPT);
	REGN(186, 2);
	REGN(187, 5, HEADER_CZ_STATUS_CHANGE, PROTOID_CZ_STATUS_CHANGE, PACKET_CZ_STATUS_CHANGE);
	REGN(188, 6, HEADER_ZC_STATUS_CHANGE_ACK, PROTOID_ZC_STATUS_CHANGE_ACK, PACKET_ZC_STATUS_CHANGE_ACK);
	REGN(189, 44, HEADER_ZC_STATUS, PROTOID_ZC_STATUS, PACKET_ZC_STATUS);
	REGN(190, 5, HEADER_ZC_STATUS_CHANGE, PROTOID_ZC_STATUS_CHANGE, PACKET_ZC_STATUS_CHANGE);
	REGN(191, 3, HEADER_CZ_REQ_EMOTION, PROTOID_CZ_REQ_EMOTION, PACKET_CZ_REQ_EMOTION);
	REGN(192, 7, HEADER_ZC_EMOTION, PROTOID_ZC_EMOTION, PACKET_ZC_EMOTION);
	REGN(193, 2, HEADER_CZ_REQ_USER_COUNT, PROTOID_CZ_REQ_USER_COUNT, PACKET_CZ_REQ_USER_COUNT);
	REGN(194, 6, HEADER_ZC_USER_COUNT, PROTOID_ZC_USER_COUNT, PACKET_ZC_USER_COUNT);
	REGN(195, 8, HEADER_ZC_SPRITE_CHANGE, PROTOID_ZC_SPRITE_CHANGE, PACKET_ZC_SPRITE_CHANGE);
	REGN(196, 6);
	REGN(197, 7);
	REGV(198, 4);
	REGV(199, 4);
	REGV(200, 4);
	REGV(201, 4);
	REGN(202, 3);
	REGN(203, 3);
	REGN(204, 6);
	REGN(205, 3);
	REGN(206, 2);
	REGN(207, 27);
	REGN(208, 3);
	REGN(209, 4);
	REGN(210, 4);
	REGN(211, 2);
	REGV(212, 4);
	REGV(213, 15);
	REGN(214, 3);
	REGV(215, 17);
	REGN(216, 6);
	REGN(217, 14);
	REGN(218, 3);
	REGV(219, 8);
	REGN(220, 28);
	REGN(221, 29);
	REGV(222, 15);
	REGV(223, 17);
	REGN(224, 30);
	REGN(225, 30);
	REGN(226, 26);
	REGN(227, 2);
	REGN(228, 6);
	REGN(229, 26);
	REGN(230, 3);
	REGN(231, 3);
	REGN(232, 8);
	REGN(233, 19);
	REGN(234, 5);
	REGN(235, 2);
	REGN(236, 3);
	REGN(237, 2);
	REGN(238, 2);
	REGN(239, 2);
	REGN(240, 3);
	REGN(241, 2);
	REGN(242, 6);
	REGN(243, 8);
	REGN(244, 21);
	REGN(245, 8);
	REGN(246, 8);
	REGN(247, 2);
	REGN(248, 2);
	REGN(249, 26);
	REGN(250, 3, HEADER_ZC_ACK_MAKE_GROUP, PROTOID_ZC_ACK_MAKE_GROUP, PACKET_ZC_ACK_MAKE_GROUP);
	REGV(251, 28, HEADER_ZC_GROUP_LIST, PROTOID_ZC_GROUP_LIST, PACKET_ZC_GROUP_LIST);
	REGN(252, 6, HEADER_CZ_REQ_JOIN_GROUP, PROTOID_CZ_REQ_JOIN_GROUP, PACKET_CZ_REQ_JOIN_GROUP);
	REGN(253, 27);
	REGN(254, 30);
	REGN(255, 10);
	REGN(256, 2);
	REGN(257, 6, HEADER_ZC_GROUPINFO_CHANGE, PROTOID_ZC_GROUPINFO_CHANGE, PACKET_ZC_GROUPINFO_CHANGE);
	REGN(258, 6);
	REGN(259, 30);
	REGN(260, 79, HEADER_ZC_ADD_MEMBER_TO_GROUP, PROTOID_ZC_ADD_MEMBER_TO_GROUP, PACKET_ZC_ADD_MEMBER_TO_GROUP);
	REGN(261, 31);
	REGN(262, 10);
	REGN(263, 10);
	REGV(264, 4);
	REGV(265, 8);
	REGN(266, 4);
	REGN(267, 6);
	REGN(268, 6);
	REGN(269, 2);
	REGN(270, 11);
	REGV(271, 4, HEADER_ZC_SKILLINFO_LIST, PROTOID_ZC_SKILLINFO_LIST, PACKET_ZC_SKILLINFO_LIST);
	REGN(272, 10, HEADER_ZC_ACK_TOUSESKILL, PROTOID_ZC_ACK_TOUSESKILL, PACKET_ZC_ACK_TOUSESKILL);
	REGN(273, 39, HEADER_ZC_ADD_SKILL, PROTOID_ZC_ADD_SKILL, PACKET_ZC_ADD_SKILL);
	REGN(274, 4, HEADER_CZ_UPGRADE_SKILLLEVEL, PROTOID_CZ_UPGRADE_SKILLLEVEL, PACKET_CZ_UPGRADE_SKILLLEVEL);
	REGN(275, 10);
	REGN(276, 31);
	REGN(277, 35);
	REGN(278, 10);
	REGN(279, 18, HEADER_ZC_NOTIFY_GROUNDSKILL, PROTOID_ZC_NOTIFY_GROUNDSKILL, PACKET_ZC_NOTIFY_GROUNDSKILL);
	REGN(280, 2, HEADER_CZ_CANCEL_LOCKON, PROTOID_CZ_CANCEL_LOCKON, PACKET_CZ_CANCEL_LOCKON);
	REGN(281, 13, HEADER_ZC_STATE_CHANGE, PROTOID_ZC_STATE_CHANGE, PACKET_ZC_STATE_CHANGE);
	REGN(282, 15);
	REGN(283, 20);
	REGN(284, 68);
	REGN(285, 2);
	REGN(286, 3);
	REGN(287, 16, HEADER_ZC_SKILL_ENTRY, PROTOID_ZC_SKILL_ENTRY, PACKET_ZC_SKILL_ENTRY);
	REGN(288, 6, HEADER_ZC_SKILL_DISAPPEAR, PROTOID_ZC_SKILL_DISAPPEAR, PACKET_ZC_SKILL_DISAPPEAR);
	REGN(289, 14, HEADER_ZC_NOTIFY_CARTITEM_COUNTINFO, PROTOID_ZC_NOTIFY_CARTITEM_COUNTINFO, PACKET_ZC_NOTIFY_CARTITEM_COUNTINFO);
	REGV(290, 4);
	REGV(291, 4, HEADER_ZC_CART_NORMAL_ITEMLIST, PROTOID_ZC_CART_NORMAL_ITEMLIST, PACKET_ZC_CART_NORMAL_ITEMLIST);
	REGN(292, 21);
	REGN(293, 8);
	REGN(294, 8);
	REGN(295, 8);
	REGN(296, 8);
	REGN(297, 8);
	REGN(298, 2, HEADER_CZ_REQ_CARTOFF, PROTOID_CZ_REQ_CARTOFF, PACKET_CZ_REQ_CARTOFF);
	REGN(299, 2, HEADER_ZC_CARTOFF, PROTOID_ZC_CARTOFF, PACKET_ZC_CARTOFF);
	REGN(300, 3);
	REGN(301, 4);
	REGN(302, 2);
	REGV(303, 84);
	REGN(304, 6);
	REGN(305, 86);
	REGN(306, 6);
	REGV(307, 8);
	REGV(308, 8);
	REGN(309, 7);
	REGV(310, 8);
	REGN(311, 6);
	REGN(312, 3);
	REGN(313, 16);
	REGN(314, 4, HEADER_ZC_ATTACK_RANGE, PROTOID_ZC_ATTACK_RANGE, PACKET_ZC_ATTACK_RANGE);
	REGN(315, 4);
	REGN(316, 4);
	REGN(317, 6);
	REGN(318, 24);
	REGN(319, 26);
	REGN(320, 22);
	REGN(321, 14, HEADER_ZC_COUPLESTATUS, PROTOID_ZC_COUPLESTATUS, PACKET_ZC_COUPLESTATUS);
	REGN(322, 6);
	REGN(323, 10);
	REGN(324, 23);
	REGN(325, 19, HEADER_ZC_SHOW_IMAGE, PROTOID_ZC_SHOW_IMAGE, PACKET_ZC_SHOW_IMAGE);
	REGN(326, 6, HEADER_CZ_CLOSE_DIALOG, PROTOID_CZ_CLOSE_DIALOG, PACKET_CZ_CLOSE_DIALOG);
	REGN(327, 39, HEADER_ZC_AUTORUN_SKILL, PROTOID_ZC_AUTORUN_SKILL, PACKET_ZC_AUTORUN_SKILL);
	REGN(328, 8);
	REGN(329, 9);
	REGN(330, 6);
	REGN(331, 27);
	REGV(332, 4);
	REGN(333, 2, HEADER_CZ_REQ_GUILD_MENUINTERFACE, PROTOID_CZ_REQ_GUILD_MENUINTERFACE, PACKET_CZ_REQ_GUILD_MENUINTERFACE);
	REGN(334, 6, HEADER_ZC_ACK_GUILD_MENUINTERFACE, PROTOID_ZC_ACK_GUILD_MENUINTERFACE, PACKET_ZC_ACK_GUILD_MENUINTERFACE);
	REGN(335, 6, HEADER_CZ_REQ_GUILD_MENU, PROTOID_CZ_REQ_GUILD_MENU, PACKET_CZ_REQ_GUILD_MENU);
	REGN(336, 110);
	REGN(337, 6);
	REGV(338, 12);
	REGV(339, 4);
	REGV(340, 4);
	REGV(341, 4);
	REGV(342, 4);
	REGN(343, 6);
//	REG?(344, ?, XXXXX_HEADER_ZC_ACK_OPEN_MEMBER_INFO); // no-len
	REGN(345, 54);
	REGN(346, 66);
	REGN(347, 54);
	REGN(348, 90);
	REGN(349, 42);
	REGN(350, 6);
	REGN(351, 42);
	REGV(352, 4);
	REGV(353, 4);
	REGV(354, 6);
	REGV(355, 4);
	REGV(356, 4);
	REGN(357, 30);
	REGV(358, 4);
	REGN(359, 3);
	REGN(360, 14);
	REGN(361, 3);
	REGN(362, 30);
	REGN(363, 10);
	REGN(364, 43, HEADER_ZC_UPDATE_GDID, PROTOID_ZC_UPDATE_GDID, PACKET_ZC_UPDATE_GDID);
	REGN(365, 14);
	REGN(366, 186);
	REGN(367, 182, HEADER_ZC_GUILD_NOTICE, PROTOID_ZC_GUILD_NOTICE, PACKET_ZC_GUILD_NOTICE);
	REGN(368, 14);
	REGN(369, 30);
	REGN(370, 10);
	REGN(371, 3);
	REGV(372, 4);
	REGN(373, 6);
	REGN(374, 106);
	REGV(375, 4);
	REGN(376, 4);
	REGN(377, 5);
	REGN(378, 4);
	REGV(379, 4);
	REGN(380, 6);
	REGN(381, 7);
	REGV(382, 4);
	REGV(383, 4);
	REGN(384, 6);
	REGN(385, 3);
	REGN(386, 106);
	REGN(387, 10);
	REGN(388, 10);
	REGN(389, 34);
//	REG?(390, ?, HEADER_COLLECTORDEAD); // no-len
	REGN(391, 6, HEADER_SC_PING, PROTOID_SC_PING, PACKET_SC_PING);
	REGN(392, 8);
	REGN(393, 4);
	REGN(394, 4);
	REGN(395, 4, HEADER_ZC_ACK_REQ_DISCONNECT, PROTOID_ZC_ACK_REQ_DISCONNECT, PACKET_ZC_ACK_REQ_DISCONNECT);
	REGN(396, 29);
	REGV(397, 4);
	REGN(398, 10);
	REGN(399, 6);
	REGN(400, 90);
	REGN(401, 86);
	REGN(402, 24);
	REGN(403, 6);
	REGN(404, 30, HEADER_ZC_ACK_REQNAME_BYGID, PROTOID_ZC_ACK_REQNAME_BYGID, PACKET_ZC_ACK_REQNAME_BYGID);
	REGN(405, 102, HEADER_ZC_ACK_REQNAMEALL, PROTOID_ZC_ACK_REQNAMEALL, PACKET_ZC_ACK_REQNAMEALL);
	REGN(406, 9, HEADER_ZC_MSG_STATE_CHANGE, PROTOID_ZC_MSG_STATE_CHANGE, PACKET_ZC_MSG_STATE_CHANGE);
	REGN(407, 4);
	REGN(408, 8);
	REGN(409, 4);
	REGN(410, 14);
	REGN(411, 10);
	REGV(412, 4);
	REGN(413, 6);
	REGN(414, 2);
	REGN(415, 6);
	REGN(416, 3);
	REGN(417, 3);
	REGN(418, 37);
	REGN(419, 5);
	REGN(420, 11);
	REGN(421, 26);
	REGV(422, 4);
	REGN(423, 4);
	REGN(424, 4);
	REGN(425, 6);
	REGN(426, 10);
	REGN(427, 12);
	REGN(428, 6);
	REGV(429, 4);
	REGN(430, 4);
	REGN(431, 4);
	REGN(432, 11);
	REGN(433, 7);
	REGV(434, 85);
	REGN(435, 67, HEADER_ZC_SHOW_IMAGE2, PROTOID_ZC_SHOW_IMAGE, PACKET_ZC_SHOW_IMAGE2);
	REGN(436, 12);
	REGN(437, 18);
	REGN(438, 114);
	REGN(439, 6);
	REGN(440, 3);
	REGN(441, 6);
	REGN(442, 26);
	REGN(443, 26);
	REGN(444, 26);
	REGN(445, 26);
	REGN(446, 2);
	REGN(447, 3);
	REGN(448, 2);
	REGN(449, 14);
	REGN(450, 10);
	REGV(451, 16);
	REGN(452, 22);
	REGN(453, 22);
	REGN(454, 4);
	REGN(455, 2);
	REGN(456, 13, HEADER_ZC_USE_ITEM_ACK2, PROTOID_ZC_USE_ITEM_ACK, PACKET_ZC_USE_ITEM_ACK2);
	REGN(457, 97, HEADER_ZC_SKILL_ENTRY2, PROTOID_ZC_SKILL_ENTRY, PACKET_ZC_SKILL_ENTRY2);
	REGN(458, 3);
	REGN(459, 9);
	REGN(460, 9);
	REGN(461, 30);
	REGN(462, 6);
	REGN(463, 28);
	REGN(464, 8);
	REGN(465, 14);
	REGN(466, 10);
	REGN(467, 35);
	REGN(468, 6);
	REGV(469, 8);
	REGN(470, 4, HEADER_ZC_NOTIFY_MAPPROPERTY2, PROTOID_ZC_NOTIFY_MAPPROPERTY2, PACKET_ZC_NOTIFY_MAPPROPERTY2);
	REGN(471, 11, HEADER_ZC_SPRITE_CHANGE2, PROTOID_ZC_SPRITE_CHANGE, PACKET_ZC_SPRITE_CHANGE2);
	REGN(472, 54);
	REGN(473, 53);
	REGN(474, 60);
	REGN(475, 2);
	REGV(476, 4);
	REGN(477, 47);
	REGN(478, 33);
	REGN(479, 6);
	REGN(480, 30);
	REGN(481, 8);
	REGN(482, 34);
	REGN(483, 14);
	REGN(484, 2);
	REGN(485, 6);
	REGN(486, 26);
	REGN(487, 2);
	REGN(488, 28);
	REGN(489, 81, HEADER_ZC_ADD_MEMBER_TO_GROUP2, PROTOID_ZC_ADD_MEMBER_TO_GROUP, PACKET_ZC_ADD_MEMBER_TO_GROUP2);
	REGN(490, 6);
	REGN(491, 10);
	REGN(492, 26);
	REGN(493, 2);
	REGV(494, 4, HEADER_ZC_NORMAL_ITEMLIST2, PROTOID_ZC_NORMAL_ITEMLIST, PACKET_ZC_NORMAL_ITEMLIST2);
	REGV(495, 4, HEADER_ZC_CART_NORMAL_ITEMLIST2, PROTOID_ZC_CART_NORMAL_ITEMLIST, PACKET_ZC_CART_NORMAL_ITEMLIST2);
	REGV(496, 4);
	REGV(497, 4);
	REGN(498, 20);
	REGN(499, 10);
	REGN(500, 32);
	REGN(501, 9);
	REGN(502, 34);
	REGN(503, 14);
	REGN(504, 2);
	REGN(505, 6);
	REGN(506, 48);
	REGN(507, 56);
	REGV(508, 4);
	REGN(509, 15);
	REGN(510, 5);
	REGN(511, 10);
	REGN(512, 26);
	REGV(513, 4);
	REGN(514, 26);
	REGN(515, 10);
	REGN(516, 18);
	REGN(517, 26);
	REGN(518, 11);
	REGN(519, 34);
	REGN(520, 14);
	REGN(521, 36);
	REGN(522, 10);
//	REG?(523, ?, HEADER_CH_EXE_HASHCHECK); // no-len
//	REG?(524, ?, HEADER_CZ_EXE_HASHCHECK); // no-len
	REGV(525, 4);
	REGN(526, 32);
//	REG?(527, ?, HEADER_CZ_REQ_PVPPOINT); // no-len
//	REG?(528, ?, HEADER_ZC_ACK_PVPPOINT); // no-len
//	REG?(529, ?, HEADER_ZH_MOVE_PVPWORLD); // no-len
	REGN(530, 26);
	REGN(531, 26);
	REGN(532, 42);
	REGN(533, 6);
	REGN(534, 6);
	REGN(535, 2);
	REGN(536, 2);
	REGN(537, 282);
	REGN(538, 282);
	REGN(539, 10);
	REGN(540, 10);
	REGN(541, 6);
	REGN(542, 6);
	REGN(543, 66);
	REGN(544, 10);
	REGV(545, 4);
	REGN(546, 6);
	REGN(547, 8);
	REGN(548, 10);
	REGN(549, 2);
	REGN(550, 282);
	REGN(551, 18);
	REGN(552, 18);
	REGN(553, 15, HEADER_ZC_STATE_CHANGE3, PROTOID_ZC_STATE_CHANGE, PACKET_ZC_STATE_CHANGE3);
	REGN(554, 58);
	REGN(555, 57);
	REGN(556, 65);
	REGN(557, 5);
	REGN(558, 71);
	REGN(559, 5);
	REGN(560, 12);
	REGN(561, 26);
	REGN(562, 9);
	REGN(563, 11);
	REGN(564, 6);
	REGV(565, 4);
	REGN(566, 10);
	REGN(567, 2);
	REGN(568, 282);
	REGN(569, 11);
	REGN(570, 4);
	REGN(571, 36);
	REGN(572, 6);
	REGN(573, 6);
	REGN(574, 8);
	REGN(575, 2);
	REGV(576, 8);
	REGN(577, 6);
	REGV(578, 99);
	REGN(579, 6);
	REGN(580, 6);
	REGN(581, 3);
	REGN(582, 4);
	REGN(583, 8);
	REGV(584, 68);
	REGN(585, 3);
	REGN(586, 70);
	REGN(587, 4);
	REGN(588, 8);
	REGN(589, 12);
	REGN(590, 6);
	REGN(591, 10);
	REGN(592, 3);
	REGN(593, 34);
	REGV(594, 12);
	REGN(595, 3);
	REGN(596, 3);
	REGN(597, 5);
	REGN(598, 5);
	REGN(599, 8);
	REGN(600, 2);
	REGN(601, 3);
	REGV(602, 4);
	REGN(603, 6);
	REGN(604, 4);
	REGN(605, 6);
	REGN(606, 4);
	REGN(607, 6);
	REGN(608, 6);
	REGN(609, 11);
	REGN(610, 11);
	REGN(611, 11);
	REGN(612, 20);
	REGN(613, 20);
	REGN(614, 30);
	REGN(615, 4);
	REGN(616, 4);
	REGN(617, 4);
	REGN(618, 4);
	REGN(619, 4);
	REGN(620, 4);
	REGN(621, 4);
//	REG?(622, ?, HEADER_AC_ACK_AUTHEKEY_FAIL_NOTMATCHCARDPASS); // no-len
	REGN(623, 2);
	REGN(624, 2);
	REGN(625, 40);
	REGN(626, 44);
	REGN(627, 30);
	REGN(628, 8);
	REGN(629, 37);
	REGV(630, 51);
	REGN(631, 84);
	REGN(632, 2);
	REGN(633, 2);
	REGV(634, 4);
	REGN(635, 14);
	REGN(636, 60);
	REGN(637, 62);
	REGV(638, 6);
	REGN(639, 8);
	REGN(640, 12);
	REGN(641, 4);
	REGN(642, 284);
	REGN(643, 6, HEADER_ZC_AID, PROTOID_ZC_AID, PACKET_ZC_AID);
	REGN(644, 14);
	REGN(645, 6);
	REGN(646, 4);
	REGV(647, 8);
	REGN(648, 6);
	REGN(649, 8);
	REGN(650, 18);
	REGV(651, 4);
	REGN(652, 46);
	REGN(653, 34);
	REGN(654, 4);
	REGN(655, 6);
	REGN(656, 4);
	REGN(657, 4, HEADER_ZC_MSG, PROTOID_ZC_MSG, PACKET_ZC_MSG);
	REGN(658, 2);
	REGN(659, 70);
	REGN(660, 10);
	REGV(661, 4, HEADER_ZC_EQUIPMENT_ITEMLIST2, PROTOID_ZC_EQUIPMENT_ITEMLIST, PACKET_ZC_EQUIPMENT_ITEMLIST2);
	REGV(662, 4);
	REGV(663, 4);
	REGN(664, 8);
	REGN(665, 6);
	REGN(666, 27, HEADER_ZC_ITEM_PICKUP_ACK2, PROTOID_ZC_ITEM_PICKUP_ACK, PACKET_ZC_ITEM_PICKUP_ACK2);
	REGN(667, 80);
	REGN(668, 66);
	REGV(669, 4);
	REGN(670, 11);
	REGN(671, 3);
//	REG?(672, ?, UNUSED_HEADER_CZ_MER_USE_SKILL); // no-len
//	REG?(673, ?, UNUSED_HEADER_CZ_MER_UPGRADE_SKILLLEVEL); // no-len
	REGN(674, 8);
//	REG?(675, ?, HEADER_ZC_GAMEGUARD_LINGO_KEY); // no-len
//	REG?(676, ?, HEADER_CZ_GAMEGUARD_LINGO_READY); // no-len
	REGN(677, 8);
	REGV(678, 10);
	REGV(679, 10);
//	REG?(680, ?, HEADER_ZC_HACKSHIELD_CRC_MSG); // no-len
//	REG?(681, ?, HEADER_CZ_HACKSHIELD_CRC_MSG); // no-len
	REGN(682, 4);
	REGN(683, 36);
	REGN(684, 6);
	REGN(685, 8);
//	REG?(686, ?, HEADER_ZC_SRPACKET_INIT); // no-len
//	REG?(687, ?, HEADER_CZ_SRPACKET_START); // no-len
	REGN(688, 85, HEADER_CA_LOGIN_CHANNEL, PROTOID_CA_LOGIN, PACKET_CA_LOGIN_CHANNEL);
	REGV(689, 8, HEADER_ZC_ALL_QUEST_LIST, PROTOID_ZC_ALL_QUEST_LIST, PACKET_ZC_ALL_QUEST_LIST);
	REGV(690, 8, HEADER_ZC_ALL_QUEST_MISSION, PROTOID_ZC_ALL_QUEST_MISSION, PACKET_ZC_ALL_QUEST_MISSION);
	REGN(691, 107);
	REGN(692, 6);
	REGV(693, 6);
	REGN(694, 7);
	REGN(695, 7);
	REGN(696, 22);
//	REGN(697, 191, HEADER_ZC_SHORTCUT_KEY_LIST, PROTOID_ZC_SHORTCUT_KEY_LIST, PACKET_ZC_SHORTCUT_KEY_LIST); // broken
	REGN(698, 11);
	REGN(699, 8);
	REGN(700, 6);
//	REG?(701, ?, HEADER_ZC_SRCRYPTOR2_INIT); // no-len
//	REG?(702, ?, HEADER_CZ_SRCRYPTOR2_START); // no-len
//	REG?(703, ?, HEADER_ZC_SRPACKETR2_INIT); // no-len
//	REG?(704, ?, HEADER_CZ_SRPACKETR2_START); // no-len
	REGV(705, 12);
	REGV(706, 6);
//	REG?(707, ?, UNUSED_HEADER_CZ_FORMATSTRING_MSG_RES); // no-len
	REGN(708, 26);
	REGN(709, 30);
	REGN(710, 30);
	REGN(711, 7);
	REGN(712, 3);
	REGN(713, 3, HEADER_ZC_PARTY_CONFIG, PROTOID_ZC_PARTY_CONFIG, PACKET_ZC_PARTY_CONFIG);
	REGN(714, 3);
	REGN(715, 65);
	REGN(716, 4);
	REGN(717, 71);
	REGN(718, 10);
	REGN(719, 6);
	REGV(720, 4);
	REGV(721, 4);
	REGV(722, 4);
	REGN(723, 4);
	REGN(724, 29, HEADER_ZC_ITEM_PICKUP_ACK3, PROTOID_ZC_ITEM_PICKUP_ACK, PACKET_ZC_ITEM_PICKUP_ACK3);
	REGN(725, 2, HEADER_ZC_ISVR_DISCONNECT, PROTOID_ZC_ISVR_DISCONNECT, PACKET_ZC_ISVR_DISCONNECT);
	REGN(726, 6);
	REGV(727, 43);
	REGN(728, 10);
	REGN(729, 10);
	REGN(730, 3, HEADER_ZC_CONFIG_NOTIFY, PROTOID_ZC_CONFIG_NOTIFY, PACKET_ZC_CONFIG_NOTIFY);
	REGV(731, 4);
	REGV(732, 32);
	REGN(733, 32);
	REGN(734, 6);
	REGN(735, 36);
	REGN(736, 34);
	REGN(737, 33);
	REGN(738, 8);
	REGN(739, 10);
	REGN(740, 6);
	REGN(741, 5);
	REGN(742, 6);
	REGV(743, 6, HEADER_ZC_MAPPROPERTY, PROTOID_ZC_MAPPROPERTY, PACKET_ZC_MAPPROPERTY);
	REGV(744, 4, HEADER_ZC_NORMAL_ITEMLIST3, PROTOID_ZC_NORMAL_ITEMLIST, PACKET_ZC_NORMAL_ITEMLIST3);
	REGV(745, 4, HEADER_ZC_CART_NORMAL_ITEMLIST3, PROTOID_ZC_CART_NORMAL_ITEMLIST, PACKET_ZC_CART_NORMAL_ITEMLIST3);
	REGV(746, 4);
	REGN(747, 13, HEADER_ZC_ACCEPT_ENTER2, PROTOID_ZC_ACCEPT_ENTER, PACKET_ZC_ACCEPT_ENTER2);
	REGN(748, 67);
	REGN(749, 59);
	REGN(750, 60);
	REGN(751, 8);
	REGN(752, 10);
	REGN(753, 2);
	REGN(754, 2);
	REGV(755, 68);
	REGN(756, 3);
	REGN(757, 7);
	REGN(758, 7);
//	...
	REGN(860, 2);
	REGV(861, 16);
	REGN(862, 2);
	REGN(863, 5, HEADER_CZ_REQUEST_MOVE2, PROTOID_CZ_REQUEST_MOVE, PACKET_CZ_REQUEST_MOVE2);
	REGN(864, 6, HEADER_CZ_REQUEST_TIME2, PROTOID_CZ_REQUEST_TIME, PACKET_CZ_REQUEST_TIME2);
	REGN(865, 5, HEADER_CZ_CHANGE_DIRECTION2, PROTOID_CZ_CHANGE_DIRECTION, PACKET_CZ_CHANGE_DIRECTION2);
	REGN(866, 6);
	REGN(867, 6);
	REGN(868, 8);
	REGN(869, 8);
	REGN(870, 10);
	REGN(871, 90);
	REGN(872, 6, HEADER_CZ_REQNAME2, PROTOID_CZ_REQNAME, PACKET_CZ_REQNAME2);
	REGN(873, 6);
//	...
	REGN(989, 18);
	REGN(990, 18);
//	REG?(991, ?, HEADER_ZC_WAITINGROOM_PARTYPLAY_JOIN); // no-len
//	REG?(992, ?, HEADER_CZ_WAITINGROOM_PARTYPLAY_JOIN_RESULT); // no-len
//	REG?(993, ?, HEADER_ZC_WAITINGROOM_SUBSCRIPTION_RESULT); // no-len
//	...
	REGN(1078, 19);
	REGN(1079, 7);
	REGN(1080, 10);
	REGN(1081, 8);
//	REG?(1082, ?, HEADER_ZC_REQ_CRACKPROOF); // no-len
//	REG?(1083, ?, HEADER_CZ_ACK_CRACKPROOF); // no-len
//	REG?(1084, ?, HEADER_ZC_CRACKPROOF_ERRCODE); // no-len
	REGN(1085, 8);
	REGV(1086, 4);
	REGN(1087, 25, HEADER_ZC_MSG_STATE_CHANGE2, PROTOID_ZC_MSG_STATE_CHANGE, PACKET_ZC_MSG_STATE_CHANGE2__COMPAT_DOWNGRADE_SC_END);
	REGN(1088, 10);
	REGN(1089, 4);
	REGV(1090, 8);
	REGN(1091, 8);
	REGV(1092, 8);
	REGN(1093, 6);
	REGN(1094, 14);
	REGN(1095, 2);
	REGV(1096, 4);
	REGN(1097, 4);
	REGN(1098, 6);
	REGN(1099, 2);
//	REG?(2000, ?, HEADER_ZC_ES_RESULT); // no-len
//	REG?(2001, ?, HEADER_CZ_ES_GET_LIST); // no-len
//	REG?(2002, ?, HEADER_ZC_ES_LIST); // no-len
//	REG?(2003, ?, HEADER_CZ_ES_CHOOSE); // no-len
//	REG?(2004, ?, HEADER_CZ_ES_CANCEL); // no-len
//	REG?(2005, ?, HEADER_ZC_ES_READY); // no-len
//	REG?(2006, ?, HEADER_ZC_ES_GOTO); // no-len
	REGN(2007, 8);
	REGN(2008, 8);
	REGN(2009, 268, HEADER_ZC_SHORTCUT_KEY_LIST_V2, PROTOID_ZC_SHORTCUT_KEY_LIST, PACKET_ZC_SHORTCUT_KEY_LIST_V2);
	REGN(2010, 6);
	REGN(2011, 8);
	REGN(2012, 6);
	REGN(2013, 54);
	REGN(2014, 30);
	REGN(2015, 54);
	REGN(2016, 58);
	REGN(2017, 15);
	REGN(2018, 8);
	REGN(2019, 6);
	REGV(2020, 12);
	REGN(2021, 4);
	REGN(2022, 8);
	REGN(2023, 32);
	REGV(2024, 4);
	REGN(2025, 5);
	REGN(2026, 2);
	REGV(2027, 8);
	REGN(2028, 8);
	REGN(2029, 10);
	REGN(2030, 6);
	REGN(2031, 8);
	REGN(2032, 6);
	REGN(2033, 18);
	REGN(2034, 8);
	REGN(2035, 6);
	REGN(2036, 3);
	REGN(2037, 6);
	REGN(2038, 14);
	REGV(2039, 69);
	REGV(2040, 62);
	REGV(2041, 63);
	REGN(2042, 8);
	REGN(2043, 25);
	REGN(2044, 10);
	REGV(2045, 7);
	REGN(2046, 26);
//	REG?(2047, ?, HEADER_ZC_DEFINE_CHECK); // no-len
	REGV(2048, 12);
	REGV(2049, 12);
	REGN(2050, 18);
	REGN(2051, 4);
	REGN(2052, 14);
	REGV(2053, 5);
	REGN(2054, 2);
	REGN(2055, 4);
	REGN(2056, 14);
	REGN(2057, 50);
	REGN(2058, 18);
	REGN(2059, 6);
	REGN(2060, 2);
	REGN(2061, 3);
	REGN(2062, 14);
	REGN(2063, 20);
	REGN(2064, 3);
	REGV(2065, 89);
	REGN(2066, 8);
	REGV(2067, 12);
	REGN(2068, 86);
	REGN(2069, 2);
	REGN(2070, 6);
	REGN(2071, 6);
	REGV(2072, 16);
	REGV(2073, 12);
	REGN(2074, 4);
	REGN(2075, 10);
	REGN(2076, 10);
	REGN(2077, 22);
	REGN(2078, 8);
	REGV(2079, 9);
	REGN(2080, 11);
	REGN(2081, 2);
	REGN(2082, 9);
	REGV(2083, 6);
	REGN(2084, 6);
	REGV(2085, 65);
	REGN(2086, 4);
	REGN(2087, 6);
	REGN(2088, 14);
	REGN(2089, 12);
	REGN(2090, 10);
	REGN(2091, 6);
	REGN(2092, 10);
	REGV(2093, 29, HEADER_HC_ACCEPT_ENTER2, PROTOID_HC_ACCEPT_ENTER, PACKET_HC_ACCEPT_ENTER2);
//	REG?(2094, ?, ?); // no-len
//	REG?(2095, ?, ?); // no-len
//	REG?(2096, ?, ?); // no-len
//	REG?(2097, ?, ?); // no-len
//	REG?(2098, ?, ?); // no-len
//	REG?(2099, ?, ?); // no-len
//	REG?(2100, ?, ?); // no-len
	REGV(2101, 15);
	REGV(2102, 7);
	REGN(2103, 3);
	REGN(2104, 2);
	REGN(2105, 66);
	REGN(2106, 5);
	REGN(2107, 2);
	REGN(2108, 12);
	REGN(2109, 6);
	REGN(2110, 26);
//	REG?(2111, ?, HEADER_ZC_SEARCH_STORE_OPEN_INFO); // no-len
	REGV(2112, 4);
	REGN(2113, 4);
	REGN(2114, 6);
	REGN(2115, 6);
	REGN(2116, 2);
	REGN(2117, 6);
	REGN(2118, 4);
	REGV(2119, 6);
	REGV(2120, 6);
	REGN(2121, 12);
	REGN(2122, 2);
	REGN(2123, 19);
	REGN(2124, 10);
	REGN(2125, 10);
	REGN(2126, 5);
	REGN(2127, 6);
	REGN(2128, 7);
	REGV(2129, 4);
	REGN(2130, 2);
	REGV(2131, 4);
	REGV(2132, 4);
	REGN(2133, 6);
	REGV(2134, 71);
	REGV(2135, 65, HEADER_ZC_NOTIFY_STANDENTRY7, PROTOID_ZC_NOTIFY_STANDENTRY, PACKET_ZC_NOTIFY_STANDENTRY7);
	REGV(2136, 64);
	REGV(2137, 45);
	REGN(2138, 2);
	REGN(2139, 2);
	REGN(2140, 2);
	REGN(2141, 2);
	REGN(2142, 2);
	REGN(2143, 2);
	REGN(2144, 2);
	REGN(2145, 2);
	REGN(2146, 2);
	REGN(2147, 2);
	REGN(2148, 2);
	REGN(2149, 2);
	REGN(2150, 2);
	REGN(2151, 2);
	REGN(2152, 2);
	REGN(2153, 2);
	REGN(2154, 2);
	REGN(2155, 2);
	REGN(2156, 2);
	REGN(2157, 2);
	REGN(2158, 2);
	REGN(2159, 2);
	REGN(2160, 2);
	REGN(2161, 2);
	REGN(2162, 2);
	REGN(2163, 2);
	REGN(2164, 2);
	REGN(2165, 2);
	REGN(2166, 2);
	REGN(2167, 2);
	REGN(2168, 2);
	REGN(2169, 2);
	REGN(2170, 2);
	REGN(2171, 2);
	REGN(2172, 2);
	REGN(2173, 2);
	REGN(2174, 2);
	REGN(2175, 2);
	REGN(2176, 2);
	REGN(2177, 2);
	REGN(2178, 2);
	REGN(2179, 2);
	REGN(2180, 2);
	REGN(2181, 2);
	REGN(2182, 2);
	REGN(2183, 2);
	REGN(2184, 2);
	REGN(2185, 2);
	REGN(2186, 2);
	REGN(2187, 2);
	REGN(2188, 2);
	REGN(2189, 2);
	REGN(2190, 2);
	REGN(2191, 2);
	REGN(2192, 2);
	REGN(2193, 2);
	REGN(2194, 2);
	REGN(2195, 2);
	REGN(2196, 2);
	REGN(2197, 2);
	REGN(2198, 2);
	REGN(2199, 2);
	REGN(2200, 2);
	REGN(2201, 2);
	REGN(2202, 2);
	REGN(2203, 2);
	REGN(2204, 2);
	REGN(2205, 2);
	REGN(2206, 2);
	REGN(2207, 2);
	REGN(2208, 2);
	REGN(2209, 2);
	REGN(2210, 2);
	REGN(2211, 2);
	REGN(2212, 2);
	REGN(2213, 2);
	REGN(2214, 2);
	REGN(2215, 2);
	REGN(2216, 2);
	REGN(2217, 2);
	REGN(2218, 2);
	REGN(2219, 2);
	REGN(2220, 2);
	REGN(2221, 2);
//	REG?(2222, ?, HEADER_CC_REPLAYPACKET); // no-len
	REGN(2223, 10);
	REGN(2224, 17);
	REGV(2225, 4);
	REGV(2226, 6);
	REGV(2227, 8);
	REGN(2228, 2);
	REGN(2229, 6);
	REGN(2230, 3);
//	REG?(2231, ?, HEADER_HC_SECOND_PASSWD_REQ); // no-len
	REGN(2232, 10);
	REGN(2233, 12);
	REGN(2234, 10);
	REGN(2235, 8);
	REGN(2236, 10);
	REGN(2237, 8);
	REGN(2238, 14);
	REGN(2239, 8);
	REGV(2240, 10);
	REGN(2241, 2);
	REGN(2242, 2);
	REGN(2243, 10);
	REGN(2244, 8);
	REGN(2245, 6);
	REGN(2246, 4);
	REGV(2247, 19, HEADER_ZC_SKILL_ENTRY3, PROTOID_ZC_SKILL_ENTRY, PACKET_ZC_SKILL_ENTRY3);
	REGN(2248, 34);
	REGN(2249, 2, HEADER_CZ_REQ_SCHEDULER_CASHITEM, PROTOID_CZ_REQ_SCHEDULER_CASHITEM, PACKET_CZ_REQ_SCHEDULER_CASHITEM);
	REGV(2250, 8, HEADER_ZC_ACK_SCHEDULER_CASHITEM, PROTOID_ZC_ACK_SCHEDULER_CASHITEM, PACKET_ZC_ACK_SCHEDULER_CASHITEM);
	REGV(2251, 10);
	REGN(2252, 109);
	REGN(2253, 10);
	REGN(2254, 2);
	REGN(2255, 10);
	REGN(2256, 9);
	REGN(2257, 7);
	REGN(2258, 10);
	REGN(2259, 10);
	REGN(2260, 8);
	REGV(2261, 8);
	REGN(2262, 6);
	REGN(2263, 28);
	REGN(2264, 27);
	REGN(2265, 30);
	REGN(2266, 26);
	REGN(2267, 27);
	REGN(2268, 26);
	REGN(2269, 27);
	REGN(2270, 27);
	REGN(2271, 50);
	REGN(2272, 51);
	REGN(2273, 51);
	REGN(2274, 27);
	REGN(2275, 118);
	REGN(2276, 6);
//	REG?(2277, ?, XXX_HEADER_CZ_PARTY_RECRUIT_REQ_REGISTER); // no-len
//	REG?(2278, ?, XXX_HEADER_ZC_PARTY_RECRUIT_ACK_REGISTER); // no-len
//	REG?(2279, ?, XXX_HEADER_CZ_PARTY_RECRUIT_REQ_SEARCH); // no-len
//	REG?(2280, ?, XXX_HEADER_ZC_PARTY_RECRUIT_ACK_SEARCH); // no-len
//	REG?(2281, ?, XXX_HEADER_CZ_PARTY_RECRUIT_REQ_DELETE); // no-len
//	REG?(2282, ?, XXX_HEADER_ZC_PARTY_RECRUIT_ACK_DELETE); // no-len
//	REG?(2283, ?, XXX_HEADER_CZ_PARTY_RECRUIT_REQ_UPDATE); // no-len
//	REG?(2284, ?, XXX_HEADER_ZC_PARTY_RECRUIT_NOTIFY_INSERT); // no-len
//	REG?(2285, ?, XXX_HEADER_ZC_PARTY_RECRUIT_NOTIFY_UPDATE); // no-len
//	REG?(2286, ?, XXX_HEADER_ZC_PARTY_RECRUIT_NOTIFY_DELETE); // no-len
//	REG?(2287, ?, XXX_HEADER_CZ_PARTY_RECRUIT_ADD_FILTERLINGLIST); // no-len
//	REG?(2288, ?, XXX_HEADER_CZ_PARTY_RECRUIT_SUB_FILTERLINGLIST); // no-len
//	REG?(2289, ?, XXX_HEADER_CZ_PARTY_RECRUIT_REQ_VOLUNTEER); // no-len
//	REG?(2290, ?, XXX_HEADER_ZC_PARTY_RECRUIT_VOLUNTEER_INFO); // no-len
//	REG?(2291, ?, XXX_HEADER_ZC_PARTY_RECRUIT_PERSONAL_SETTING); // no-len
//	REG?(2292, ?, XXX_HEADER_CZ_PARTY_RECRUIT_SHOW_EQUIPMENT); // no-len
//	REG?(2293, ?, XXX_HEADER_CZ_PARTY_RECRUIT_REQ_RECALL); // no-len
//	REG?(2294, ?, XXX_HEADER_ZC_PARTY_RECRUIT_RECALL_COST); // no-len
//	REG?(2295, ?, XXX_HEADER_CZ_PARTY_RECRUIT_ACK_RECALL); // no-len
//	REG?(2296, ?, XXX_HEADER_ZC_PARTY_RECRUIT_FAILED_RECALL); // no-len
//	REG?(2297, ?, XXX_HEADER_CZ_PARTY_RECRUIT_REFUSE_VOLUNTEER); // no-len
//	REG?(2298, ?, XXX_HEADER_ZC_PARTY_RECRUIT_REFUSE_VOLUNTEER); // no-len
//	REG?(2299, ?, XXX_HEADER_CZ_PARTY_RECRUIT_CANCEL_VOLUNTEER); // no-len
	REGN(2300, 30);
	REGN(2301, 6);
	REGV(2302, 4);
	REGN(2303, 24);
	REGV(2304, 4);
	REGV(2305, 4);
	REGV(2306, 4);
	REGV(2307, 4);
	REGV(2308, 4);
	REGV(2309, 4);
	REGV(2310, 45);
	REGN(2311, 5);
	REGN(2312, 5);
//	REG?(2313, ?, XXX_HEADER_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER); // no-len
	REGN(2314, 26);
//	REG?(2315, ?, XXX_HEADER_ZC_PARTY_RECRUIT_ADD_FILTERLINGLIST); // no-len
//	REG?(2316, ?, XXX_HEADER_ZC_PARTY_RECRUIT_SUB_FILTERLINGLIST); // no-len
	REGV(2317, 10);
	REGN(2318, 2);
	REGV(2319, 73);
	REGN(2320, 10);
	REGN(2321, 30);
	REGN(2322, 10);
	REGN(2323, 30);
	REGV(2324, 80);
	REGV(2325, 74);
	REGN(2326, 26);
	REGN(2327, 2);
	REGN(2328, 2);
	REGN(2329, 2);
	REGN(2330, 2);
	REGN(2331, 2);
	REGN(2332, 2);
	REGN(2333, 2);
	REGN(2334, 2);
	REGN(2335, 2);
	REGN(2336, 2);
	REGN(2337, 2);
	REGN(2338, 2);
	REGN(2339, 2);
	REGN(2340, 2);
	REGN(2341, 2);
	REGN(2342, 2);
	REGN(2343, 2);
	REGN(2344, 2);
	REGN(2345, 2);
	REGN(2346, 2);
	REGN(2347, 2);
	REGN(2348, 2);
	REGN(2349, 2);
	REGN(2350, 2);
	REGN(2351, 2);
	REGN(2352, 2);
	REGN(2353, 2);
	REGN(2354, 2);
	REGN(2355, 2);
	REGN(2356, 2);
	REGN(2357, 2);
	REGN(2358, 2);
	REGN(2359, 2);
	REGN(2360, 2);
	REGN(2361, 2);
	REGN(2362, 2);
	REGN(2363, 2);
	REGN(2364, 2);
	REGN(2365, 2);
	REGN(2366, 2);
	REGN(2367, 2);
	REGN(2368, 2);
	REGN(2369, 2);
	REGN(2370, 2);
	REGN(2371, 2);
	REGN(2372, 2);
	REGN(2373, 2);
	REGN(2374, 2);
	REGN(2375, 2);
	REGN(2376, 2);
	REGN(2377, 2);
	REGN(2378, 2);
	REGN(2379, 2);
	REGN(2380, 2);
	REGN(2381, 2);
	REGN(2382, 2);
	REGN(2383, 2);
	REGN(2384, 2);
	REGN(2385, 2);
	REGN(2386, 2);
	REGN(2387, 2);
	REGN(2388, 2);
	REGN(2389, 2);
	REGN(2390, 2);
	REGN(2391, 2);
	REGN(2392, 2);
	REGN(2393, 2);
	REGN(2394, 2);
	REGN(2395, 2);
	REGN(2396, 2);
	REGN(2397, 2);
	REGN(2398, 2);
	REGN(2399, 2);
	REGN(2400, 2);
	REGN(2401, 2);
	REGN(2402, 2);
	REGN(2403, 2);
	REGN(2404, 2);
	REGN(2405, 2);
	REGN(2406, 2);
	REGN(2407, 2);
	REGN(2408, 2);
	REGN(2409, 2);
	REGN(2410, 2);
	REGN(2411, 4);
	REGN(2412, 6);
	REGV(2413, 4);
	REGV(2414, 4);
	REGN(2415, 7);
	REGN(2416, 31);
	REGN(2417, 6);
	REGV(2418, 9);
	REGN(2419, 7);
	REGN(2420, 2);
	REGV(2421, 28);
	REGV(2422, 28);
	REGN(2423, 14);
	REGN(2424, 6);
	REGN(2425, 50);
	REGV(2426, 8);
	REGV(2427, 16);
	REGN(2428, 4);
	REGN(2429, 288);
	REGN(2430, 12);
	REGV(2431, 8);
	REGN(2432, 7);
	REGV(2433, 12);
	REGN(2434, 7);
//	REGN(2435, 29, HEADER_ZC_MSG_STATE_CHANGE3, PROTOID_ZC_MSG_STATE_CHANGE, PACKET_ZC_MSG_STATE_CHANGE3);
	REGN(2436, 28);
	REGV(2437, 4);
	REGN(2438, 10);
	REGV(2439, 41);
	REGN(2440, 6);
	REGN(2441, 2);
	REGV(2442, 74);
	REGN(2443, 2);
	REGN(2444, 4);
	REGV(2445, 4);
	REGV(2446, 28);
	REGV(2447, 8);
	REGN(2448, 31);
	REGV(2449, 4);
	REGV(2450, 4);
	REGV(2451, 4);
	REGV(2452, 4);
	REGV(2453, 28);
	REGV(2454, 28);
	REGV(2455, 45);
	REGN(2456, 8);
	REGN(2457, 11);
	REGN(2458, 9);
	REGN(2459, 8);
	REGN(2460, 6);
	REGV(2461, 4);
	REGN(2462, 12);
	REGV(2463, 22);
	REGN(2464, 6);
	REGN(2465, 2);
	REGN(2466, 6);
	REGV(2467, 8);
	REGN(2468, 18);
	REGN(2469, 7);
	REGN(2470, 12);
	REGN(2471, 10);
	REGN(2472, 16);
	REGN(2473, 10);
	REGN(2474, 16);
	REGN(2475, 6);
	REGV(2476, 8);
	REGN(2477, 10);
	REGN(2478, 17);
	REGN(2479, 4);
	REGN(2480, 8);
	REGN(2481, 4);
	REGN(2482, 8);
	REGN(2483, 4);
	REGN(2484, 6);
	REGN(2485, 2);
	REGN(2486, 6);
	REGN(2487, 4);
	REGN(2488, 6);
	REGN(2489, 4);
	REGN(2490, 2);
	REGN(2491, 6);
	REGN(2492, 6);
	REGN(2493, 2);
	REGN(2494, 2);
	REGN(2495, 4);
//	REG?(2496, ?, HEADER_ZC_ACTION_MOVE); // no-len
	REGN(2497, 10);
	REGV(2498, 4);
	REGN(2499, 8);
	REGN(2500, 8);
	REGN(2501, 1042);
	REGV(2502, 16);
	REGN(2503, 18);
	REGV(2504, 13);
	REGV(2505, 4);
	REGV(2506, 23);
	REGN(2507, 17);
	REGV(2508, 4);
	REGN(2509, 8);
	REGN(2510, 102);
	REGV(2511, 4);
	REGV(2512, 4);
	REGN(2513, 14);
	REGV(2514, 28);
	REGV(2515, 28);
	REGN(2516, 2);
	REGV(2517, 4);
	REGV(2518, 4);
	REGV(2519, 4);
	REGN(2520, 2);
	REGN(2521, 4);
	REGN(2522, 6);
//	REGN(2523, 0, HEADER_LAST); // dummy
}
