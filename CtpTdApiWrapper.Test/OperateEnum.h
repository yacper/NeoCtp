#pragma once
enum OperateEnum			// ����ö�٣�����Ϊ64λ
{
	Auth = 1 << 0,									// ��֤
	Login = 1 << 1,									// ��¼
	Logout = 1 << 2,								// �ǳ�
	UpdateLoginPwd = 1 << 3,						// ���µ�¼����
	UpdateTrdAccountPwd = 1 << 4,					// ���½����˻�����

	OrderInsert = 1 << 5,							// ����¼��
	ParkedOrderInsert = 1 << 6,						// Ԥ��¼��
	ParkedOrderAction = 1 << 7,						// Ԥ�񳷵�¼��
	RemoveParkedOrder = 1 << 8,						// ɾ��Ԥ��

	OrderAction = 1 << 9,							// ��������
	QryOrder = 1 << 10,								// ��ѯ����
	QueryMaxOrderVolume = 1 << 11,					// ��ѯ��󶩵���
	SettlementInfoConfirm = 1 << 12,				// Ͷ���߽�����ȷ��

	ForQuoteInsert = 1 << 13,						// ��ѯ��
	QryQuote = 1 << 14,								// ��ѯ����
	QryCombAction = 1 << 15,						// ��ѯ���
	QryCombInstrumentGuard = 1 << 16,				// ��ѯ��Ϻ�Լ�İ�ȫϵ��
	QryTransferSerial = 1 << 17,					// ��ѯת����ˮ
	QryAccountregister = 1 << 18,					// ��ѯ����ǩԼ��ϵ

	QryContractBank = 1 << 19,						// ��ѯǩԼ����
	QryParkedOrder = 1 << 20,						// ��ѯԤ�񶩵�
	QryParkedOrderAction = 1 << 21,					// ��ѯԤ�񳷵�
	QryTradingNotice = 1 << 22,						// ��ѯ����֪ͨ
	QryBrokerTradingParams = 1 << 23,				// ��ѯ���ù�˾���ײ���

	QryBrokerTradingAlgos = 1 << 24,				// ��ѯ���ù�˾�Ľ����㷨
	QueryBankBalanceByFuture = 1 << 25,				// ��ѯ�ڻ��������
	QueryCFMMCTradingAccountToken = 1 << 26,		// ��ѯ��������û�����
	ReqFromBankToFutureByFuture = 1 << 27,			// �ڻ���������ת�ڻ�����
	ReqFromFutureToBankByFuture = 1 << 28,			// �ڻ������ڻ�ת��������

	ReqQryInvestUnit = 1 << 29,						// �����ѯͶ�ʵ�Ԫ
	ReqQrySecAgentTradeInfo = 1 << 30,				// �����ѯ������������Ϣ
	ReqQrySecAgentCheckMode = 1 << 31,				// �����ѯ�����������ʽ���֤ģʽ
	ReqQrySecAgentTradingAccount = 1 << 32,			// �����ѯ�ʽ��˻�
	ReqQryInstrumentOrderCommRate = 1 << 33,		// ���󱨵�������
	ReqQryMMInstrumentCommissionRate = 1 << 34,		// �����ѯ������������

	ReqQryProductGroup = 1 << 35,					// �����ѯ��Ʒ��
	ReqQryProductExchRate = 1 << 36,				// �����ѯ��Ʒ���ۻ���
	ReqQryExchangeRate = 1 << 37,					// �����ѯ����
	ReqQryExchangeMarginRateAdjust = 1 << 38,		// �������������ı�֤��
	ReqQryExchangeMarginRate = 1 << 39,				// �����ѯ��������֤����
	ReqQryInvestorProductGroupMargin = 1 << 40,		// �����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��

	ReqQryEWarrantOffset = 1 << 41,					// �����ѯ�ֲ���Ϣ
	ReqQryCFMMCTradingAccountKey = 1 << 42,			// �����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
	ReqQryInvestorPositionCombineDetail = 1 << 43,	// �����ѯͶ������Ϻ�Լ�ֲ���ϸ
	ReqQryInvestorPositionDetail = 1 << 44,			// �����ѯͶ���ߺ�Լ�ֲ���ϸ
	ReqQryTransferBank = 1 << 45,					// �����ѯת������

	ReqQrySettlementInfo = 1 << 46,					// �����ѯͶ���߽�����Ϣ
	ReqQryDepthMarketData = 1 << 47,				// �����ѯ��������
	ReqQryInstrument = 1 << 48,						// �����ѯ��Լ
	ReqQryExchange = 1 << 49,						// �����ѯ������
	ReqQryInstrumentCommissionRate = 1 << 50,		// �����ѯ��Լ������
	ReqQryInstrumentMarginRate = 1 << 51,			// �����ѯ��Լ�ı�֤����

	ReqQryTradingCode = 1 << 52,					// �����ѯ�����߱��
	ReqQryInvestor = 1 << 53,						// �����ѯͶ����
	ReqQryTradingAccount = 1 << 54,					// �����ѯ�ʽ��˻�
	ReqQryInvestorPosition = 1 << 55,				// �����ѯͶ���ֲ߳�
	ReqQryTrade = 1 << 56,							// �����ѯ����
};