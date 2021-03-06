
#include "stdafx.h"
#include "TradeApi.h"
#include "..\api\ThostFtdcUserApiDataType.h"
#include "..\api\ThostFtdcUserApiStruct.h"

// UserApi对象
CThostFtdcTraderApi* pUserApi;

//回调函数
CBOnFrontConnected cbOnFrontConnected=0;		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
CBOnFrontDisconnected cbOnFrontDisconnected=0;		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
CBOnHeartBeatWarning cbOnHeartBeatWarning=0;		///心跳超时警告。当长时间未收到报文时，该方法被调用。
CBRspUserLogin cbRspUserLogin=0;	///登录请求响应
CBRspUserLogout cbRspUserLogout=0;	///登出请求响应
CBRspUserPasswordUpdate cbRspUserPasswordUpdate=0;	///用户口令更新请求响应
CBRspTradingAccountPasswordUpdate cbRspTradingAccountPasswordUpdate=0;	///资金账户口令更新请求响应
CBRspOrderInsert cbRspOrderInsert=0;	///报单录入请求响应
CBRspParkedOrderInsert cbRspParkedOrderInsert=0;	///预埋单录入请求响应
CBRspParkedOrderAction cbRspParkedOrderAction=0;	///预埋撤单录入请求响应
CBRspOrderAction cbRspOrderAction=0;	///报单操作请求响应
CBRspQueryMaxOrderVolume cbRspQueryMaxOrderVolume=0;	///查询最大报单数量响应
CBRspSettlementInfoConfirm cbRspSettlementInfoConfirm=0;	///投资者结算结果确认响应
CBRspRemoveParkedOrder cbRspRemoveParkedOrder=0;	///删除预埋单响应
CBRspRemoveParkedOrderAction cbRspRemoveParkedOrderAction=0;	///删除预埋撤单响应
CBRspQryOrder cbRspQryOrder=0;	///请求查询报单响应
CBRspQryTrade cbRspQryTrade=0;	///请求查询成交响应
CBRspQryInvestorPosition cbRspQryInvestorPosition=0;	///请求查询投资者持仓响应
CBRspQryTradingAccount cbRspQryTradingAccount=0;	///请求查询资金账户响应
CBRspQryInvestor cbRspQryInvestor=0;	///请求查询投资者响应
CBRspQryTradingCode cbRspQryTradingCode=0;	///请求查询交易编码响应
CBRspQryInstrumentMarginRate cbRspQryInstrumentMarginRate=0;	///请求查询合约保证金率响应
CBRspQryInstrumentCommissionRate cbRspQryInstrumentCommissionRate=0;	///请求查询合约手续费率响应
CBRspQryExchange cbRspQryExchange=0;	///请求查询交易所响应
CBRspQryInstrument cbRspQryInstrument=0;	///请求查询合约响应
CBRspQryDepthMarketData cbRspQryDepthMarketData=0;	///请求查询行情响应
CBRspQrySettlementInfo cbRspQrySettlementInfo=0;	///请求查询投资者结算结果响应
CBRspQryTransferBank cbRspQryTransferBank=0;	///请求查询转帐银行响应
CBRspQryInvestorPositionDetail cbRspQryInvestorPositionDetail=0;	///请求查询投资者持仓明细响应
CBRspQryNotice cbRspQryNotice=0;	///请求查询客户通知响应
CBRspQrySettlementInfoConfirm cbRspQrySettlementInfoConfirm=0;	///请求查询结算信息确认响应
CBRspQryInvestorPositionCombineDetail cbRspQryInvestorPositionCombineDetail=0;	///请求查询投资者持仓明细响应
CBRspQryCFMMCTradingAccountKey cbRspQryCFMMCTradingAccountKey=0;	///查询保证金监管系统经纪公司资金账户密钥响应
CBRspQryTransferSerial cbRspQryTransferSerial=0;	///请求查询转帐流水响应
CBRspQryAccountregister cbRspQryAccountregister =0;///请求查询银期签约关系响应
CBRspError cbRspError=0;	///错误应答
CBRtnOrder cbRtnOrder=0;	///报单通知
CBRtnTrade cbRtnTrade=0;	///成交通知
CBErrRtnOrderInsert cbErrRtnOrderInsert=0;	///报单录入错误回报
CBErrRtnOrderAction cbErrRtnOrderAction=0;	///报单操作错误回报
CBRtnInstrumentStatus cbRtnInstrumentStatus=0;	///合约交易状态通知
CBRtnTradingNotice cbRtnTradingNotice=0;	///交易通知
CBRtnErrorConditionalOrder cbRtnErrorConditionalOrder=0;	///提示条件单校验错误
CBRspQryContractBank cbRspQryContractBank=0;	///请求查询签约银行响应
CBRspQryParkedOrder cbRspQryParkedOrder=0;	///请求查询预埋单响应
CBRspQryParkedOrderAction cbRspQryParkedOrderAction=0;	///请求查询预埋撤单响应
CBRspQryTradingNotice cbRspQryTradingNotice=0;	///请求查询交易通知响应
CBRspQryBrokerTradingParams cbRspQryBrokerTradingParams=0;	///请求查询经纪公司交易参数响应
CBRspQryBrokerTradingAlgos cbRspQryBrokerTradingAlgos=0;	///请求查询经纪公司交易算法响应
CBRtnFromBankToFutureByBank cbRtnFromBankToFutureByBank=0;	///银行发起银行资金转期货通知
CBRtnFromFutureToBankByBank cbRtnFromFutureToBankByBank=0;	///银行发起期货资金转银行通知
CBRtnRepealFromBankToFutureByBank cbRtnRepealFromBankToFutureByBank=0;	///银行发起冲正银行转期货通知
CBRtnRepealFromFutureToBankByBank cbRtnRepealFromFutureToBankByBank=0;	///银行发起冲正期货转银行通知
CBRtnFromBankToFutureByFuture cbRtnFromBankToFutureByFuture=0;	///期货发起银行资金转期货通知
CBRtnFromFutureToBankByFuture cbRtnFromFutureToBankByFuture=0;	///期货发起期货资金转银行通知
CBRtnRepealFromBankToFutureByFutureManual cbRtnRepealFromBankToFutureByFutureManual=0;	///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
CBRtnRepealFromFutureToBankByFutureManual cbRtnRepealFromFutureToBankByFutureManual=0;	///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
CBRtnQueryBankBalanceByFuture cbRtnQueryBankBalanceByFuture=0;	///期货发起查询银行余额通知
CBErrRtnBankToFutureByFuture cbErrRtnBankToFutureByFuture=0;	///期货发起银行资金转期货错误回报
CBErrRtnFutureToBankByFuture cbErrRtnFutureToBankByFuture=0;	///期货发起期货资金转银行错误回报
CBErrRtnRepealBankToFutureByFutureManual cbErrRtnRepealBankToFutureByFutureManual=0;	///系统运行时期货端手工发起冲正银行转期货错误回报
CBErrRtnRepealFutureToBankByFutureManual cbErrRtnRepealFutureToBankByFutureManual=0;	///系统运行时期货端手工发起冲正期货转银行错误回报
CBErrRtnQueryBankBalanceByFuture cbErrRtnQueryBankBalanceByFuture=0;	///期货发起查询银行余额错误回报
CBRtnRepealFromBankToFutureByFuture cbRtnRepealFromBankToFutureByFuture=0;	///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
CBRtnRepealFromFutureToBankByFuture cbRtnRepealFromFutureToBankByFuture=0;	///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
CBRspFromBankToFutureByFuture cbRspFromBankToFutureByFuture=0;	///期货发起银行资金转期货应答
CBRspFromFutureToBankByFuture cbRspFromFutureToBankByFuture=0;	///期货发起期货资金转银行应答
CBRspQueryBankAccountMoneyByFuture cbRspQueryBankAccountMoneyByFuture=0;	///期货发起查询银行余额应答
//===============

// 请求编号
int volatile iRequestID = 0;
//连接
TRADEAPI_API void Connect(char* FRONT_ADDR, char *pszFlowPath)
{
	// 初始化UserApi
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);			// 创建UserApi
	CTraderSpi* pUserSpi = new CTraderSpi();
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类
	pUserApi->SubscribePublicTopic(THOST_TERT_QUICK/*THOST_TERT_RESTART*/);					// 注册公有流
	pUserApi->SubscribePrivateTopic(THOST_TERT_QUICK/*THOST_TERT_RESTART*/);					// 注册私有流
	pUserApi->RegisterFront(FRONT_ADDR);							// connect
	pUserApi->Init();
	//pUserApi->Join();
}

TRADEAPI_API const char *GetTradingDay()
{
	return pUserApi->GetTradingDay();
}
//断开
TRADEAPI_API void DisConnect()
{
	pUserApi->Release();
}

TRADEAPI_API int GetRequestID()
{
	return iRequestID;
}

//发送用户登录请求
TRADEAPI_API int ReqUserLogin(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcUserIDType USER_ID,TThostFtdcPasswordType PASSWORD)
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID);
	strcpy_s(req.UserID, USER_ID);
	strcpy_s(req.Password, PASSWORD);
	strcpy_s(req.UserProductInfo,"HF");
	return pUserApi->ReqUserLogin(&req, ++iRequestID);
}
//发送登出请求
TRADEAPI_API int ReqUserLogout(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcUserIDType INVESTOR_ID)
{
	CThostFtdcUserLogoutField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID);
	strcpy_s(req.UserID, INVESTOR_ID);
	return pUserApi->ReqUserLogout(&req, ++iRequestID);
}
//更新用户口令
TRADEAPI_API int ReqUserPasswordUpdate(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcUserIDType USER_ID,TThostFtdcUserIDType OLD_PASSWORD,TThostFtdcPasswordType NEW_PASSWORD)
{
	CThostFtdcUserPasswordUpdateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID);
	strcpy_s(req.UserID, USER_ID);
	strcpy_s(req.OldPassword,OLD_PASSWORD);
	strcpy_s(req.NewPassword,NEW_PASSWORD);
	return pUserApi->ReqUserPasswordUpdate(&req, ++iRequestID);
}
///资金账户口令更新请求
TRADEAPI_API int ReqTradingAccountPasswordUpdate(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcAccountIDType ACCOUNT_ID,TThostFtdcUserIDType OLD_PASSWORD,TThostFtdcPasswordType NEW_PASSWORD)
{
	CThostFtdcTradingAccountPasswordUpdateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID);
	strcpy_s(req.AccountID, ACCOUNT_ID);
	strcpy_s(req.NewPassword,NEW_PASSWORD);
	strcpy_s(req.OldPassword,OLD_PASSWORD);
	return pUserApi->ReqTradingAccountPasswordUpdate(&req, ++iRequestID);
}
//报单录入请求
TRADEAPI_API int ReqOrderInsert(CThostFtdcInputOrderField *pOrder)
{
	int siez = sizeof(CThostFtdcInputOrderField);
	strcpy_s(pOrder->BusinessUnit,"HF");
	return pUserApi->ReqOrderInsert(pOrder, ++iRequestID);
}
//报单操作请求
TRADEAPI_API int ReqOrderAction(CThostFtdcInputOrderActionField *pOrder)
{
	return pUserApi->ReqOrderAction(pOrder, ++iRequestID);
}
///查询最大报单数量请求
TRADEAPI_API int ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pMaxOrderVolume)
{
	return pUserApi->ReqQueryMaxOrderVolume(pMaxOrderVolume, ++iRequestID);
}
//投资者结算结果确认
TRADEAPI_API int ReqSettlementInfoConfirm(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID)
{
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID);
	strcpy_s(req.InvestorID, INVESTOR_ID);
	return pUserApi->ReqSettlementInfoConfirm(&req, ++iRequestID);
}
///请求查询报单
TRADEAPI_API int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder)
{
	return pUserApi->ReqQryOrder(pQryOrder, ++iRequestID);
}
///请求查询成交
TRADEAPI_API int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade)
{
	return pUserApi->ReqQryTrade(pQryTrade, ++iRequestID);
}
//请求查询投资者持仓
TRADEAPI_API int ReqQryInvestorPosition(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID,TThostFtdcInstrumentIDType INSTRUMENT_ID)
{
	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID);
	strcpy_s(req.InvestorID, INVESTOR_ID);
	if(INSTRUMENT_ID != NULL)
		strcpy_s(req.InstrumentID, INSTRUMENT_ID);
	return pUserApi->ReqQryInvestorPosition(&req, ++iRequestID);
}
//请求查询资金账户
TRADEAPI_API int ReqQryTradingAccount(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID)
{
	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID);
	strcpy_s(req.InvestorID, INVESTOR_ID);
	return pUserApi->ReqQryTradingAccount(&req, ++iRequestID);
}
///请求查询投资者
TRADEAPI_API int ReqQryInvestor(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID)
{
	CThostFtdcQryInvestorField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID ,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);
	return pUserApi->ReqQryInvestor(&req, ++iRequestID);
}
	///请求查询交易编码
TRADEAPI_API int ReqQryTradingCode(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID,TThostFtdcClientIDType CLIENT_ID,TThostFtdcExchangeIDType	EXCHANGE_ID)
{
	CThostFtdcQryTradingCodeField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID ,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);
	if(CLIENT_ID != NULL)
		strcpy_s(req.ClientID,CLIENT_ID);
	if(EXCHANGE_ID != NULL)
		strcpy_s(req.ExchangeID,EXCHANGE_ID);
	return pUserApi->ReqQryTradingCode(&req, ++iRequestID);
}
	///请求查询合约保证金率
TRADEAPI_API int ReqQryInstrumentMarginRate(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID,TThostFtdcInstrumentIDType INSTRUMENT_ID,TThostFtdcHedgeFlagType	HEDGE_FLAG)
{
	CThostFtdcQryInstrumentMarginRateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID ,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);
	if(INSTRUMENT_ID != NULL)
		strcpy_s(req.InstrumentID,INSTRUMENT_ID);
	if(HEDGE_FLAG != NULL)
		req.HedgeFlag = HEDGE_FLAG;						//*不*能采用null进行所有查询
	return pUserApi->ReqQryInstrumentMarginRate(&req, ++iRequestID);
}
	///请求查询合约手续费率
TRADEAPI_API int ReqQryInstrumentCommissionRate(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID,TThostFtdcInstrumentIDType INSTRUMENT_ID)
{
	CThostFtdcQryInstrumentCommissionRateField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID ,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);	
	if(INSTRUMENT_ID != NULL)
		strcpy_s(req.InstrumentID,INSTRUMENT_ID);
	return pUserApi->ReqQryInstrumentCommissionRate(&req, ++iRequestID);
}
	///请求查询交易所
TRADEAPI_API int ReqQryExchange(TThostFtdcExchangeIDType EXCHANGE_ID)
{
	CThostFtdcQryExchangeField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.ExchangeID,EXCHANGE_ID);
	return pUserApi->ReqQryExchange(&req, ++iRequestID);
}
//请求查询合约
TRADEAPI_API int ReqQryInstrument(TThostFtdcInstrumentIDType INSTRUMENT_ID)
{
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	if(INSTRUMENT_ID != NULL)
		strcpy_s(req.InstrumentID, INSTRUMENT_ID);
	return pUserApi->ReqQryInstrument(&req, ++iRequestID);
}
//请求查询行情
TRADEAPI_API int ReqQryDepthMarketData(TThostFtdcInstrumentIDType INSTRUMENT_ID)
{
	CThostFtdcQryDepthMarketDataField req;
	memset(&req,0,sizeof(req));
	if(INSTRUMENT_ID != NULL)
		strcpy_s(req.InstrumentID, INSTRUMENT_ID);
	return pUserApi->ReqQryDepthMarketData(&req, ++iRequestID);
}
	///请求查询投资者结算结果
TRADEAPI_API int ReqQrySettlementInfo(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID,TThostFtdcDateType	TRADING_DAY)
{
	CThostFtdcQrySettlementInfoField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID ,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);	
	if(TRADING_DAY != NULL)
		strcpy_s(req.TradingDay, TRADING_DAY);
	return pUserApi->ReqQrySettlementInfo(&req, ++iRequestID);
}
//查询持仓明细
TRADEAPI_API int ReqQryInvestorPositionDetail(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID,TThostFtdcInstrumentIDType INSTRUMENT_ID)
{
	CThostFtdcQryInvestorPositionDetailField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);
	if(INSTRUMENT_ID != NULL)
		strcpy_s(req.InstrumentID, INSTRUMENT_ID);
	return pUserApi->ReqQryInvestorPositionDetail(&req, ++iRequestID);
}
	///请求查询客户通知
TRADEAPI_API int ReqQryNotice(TThostFtdcBrokerIDType BROKERID)
{
	CThostFtdcQryNoticeField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,BROKERID);
	return pUserApi->ReqQryNotice(&req, ++iRequestID);
}
	///请求查询结算信息确认
TRADEAPI_API int ReqQrySettlementInfoConfirm(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID)
{
	CThostFtdcQrySettlementInfoConfirmField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);
	return pUserApi->ReqQrySettlementInfoConfirm(&req, ++iRequestID);
}
	///请求查询**组合**持仓明细
TRADEAPI_API int ReqQryInvestorPositionCombineDetail(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID,TThostFtdcInstrumentIDType INSTRUMENT_ID)
{
	CThostFtdcQryInvestorPositionCombineDetailField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);
	if(INSTRUMENT_ID != NULL)
		strcpy_s(req.CombInstrumentID, INSTRUMENT_ID);
	return pUserApi->ReqQryInvestorPositionCombineDetail(&req, ++iRequestID);
}
	///请求查询保证金监管系统经纪公司资金账户密钥
TRADEAPI_API int ReqQryCFMMCTradingAccountKey(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID)
{
	CThostFtdcQryCFMMCTradingAccountKeyField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);
	return pUserApi->ReqQryCFMMCTradingAccountKey(&req, ++iRequestID);
}
	///请求查询交易通知
TRADEAPI_API int ReqQryTradingNotice(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID)
{
	CThostFtdcQryTradingNoticeField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);
	return pUserApi->ReqQryTradingNotice(&req, ++iRequestID);
}
	///请求查询经纪公司交易参数
TRADEAPI_API int ReqQryBrokerTradingParams(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID)
{
	CThostFtdcQryBrokerTradingParamsField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);
	return pUserApi->ReqQryBrokerTradingParams(&req, ++iRequestID);
}
	///请求查询经纪公司交易算法
TRADEAPI_API int ReqQryBrokerTradingAlgos(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcExchangeIDType EXCHANGE_ID,TThostFtdcInstrumentIDType INSTRUMENT_ID)
{
	CThostFtdcQryBrokerTradingAlgosField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,BROKER_ID);
	if(EXCHANGE_ID != NULL)
		strcpy_s(req.ExchangeID, EXCHANGE_ID);
	if(INSTRUMENT_ID != NULL)
		strcpy_s(req.InstrumentID, INSTRUMENT_ID);

	return pUserApi->ReqQryBrokerTradingAlgos(&req, ++iRequestID);
}
	///预埋单录入请求
TRADEAPI_API int ReqParkedOrderInsert(CThostFtdcParkedOrderField *ParkedOrder)
{
	return pUserApi->ReqParkedOrderInsert(ParkedOrder,++iRequestID);
}
	///预埋撤单录入请求
TRADEAPI_API int ReqParkedOrderAction(CThostFtdcParkedOrderActionField *ParkedOrderAction)
{
	return pUserApi->ReqParkedOrderAction(ParkedOrderAction,++iRequestID);
}
	///请求删除预埋单
TRADEAPI_API int ReqRemoveParkedOrder(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID,TThostFtdcParkedOrderIDType ParkedOrder_ID)
{
	CThostFtdcRemoveParkedOrderField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);
	strcpy_s(req.ParkedOrderID,ParkedOrder_ID);
	return pUserApi->ReqRemoveParkedOrder(&req, ++iRequestID);
}
	///请求删除预埋撤单
TRADEAPI_API int ReqRemoveParkedOrderAction(TThostFtdcBrokerIDType BROKER_ID,TThostFtdcInvestorIDType INVESTOR_ID,TThostFtdcParkedOrderActionIDType ParkedOrderAction_ID)
{
	CThostFtdcRemoveParkedOrderActionField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,BROKER_ID);
	strcpy_s(req.InvestorID,INVESTOR_ID);
	strcpy_s(req.ParkedOrderActionID,ParkedOrderAction_ID);
	return pUserApi->ReqRemoveParkedOrderAction(&req, ++iRequestID);
}
	///请求查询转帐银行
TRADEAPI_API int ReqQryTransferBank(TThostFtdcBankIDType Bank_ID,	TThostFtdcBankBrchIDType BankBrch_ID)
{
	CThostFtdcQryTransferBankField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BankID,Bank_ID);
	strcpy_s(req.BankBrchID,BankBrch_ID);
	return pUserApi->ReqQryTransferBank(&req, ++iRequestID);
}
	///请求查询转帐流水
TRADEAPI_API int ReqQryTransferSerial(TThostFtdcBrokerIDType Broker_ID,TThostFtdcAccountIDType Account_ID,TThostFtdcBankIDType Bank_ID)
{ 
	CThostFtdcQryTransferSerialField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,Broker_ID);
	strcpy_s(req.AccountID,Account_ID);
	strcpy_s(req.BankID,Bank_ID);
	return pUserApi->ReqQryTransferSerial(&req, ++iRequestID);
}
///请求查询银期签约关系
TRADEAPI_API int ReqQryAccountregister(TThostFtdcBrokerIDType Broker_ID, TThostFtdcAccountIDType Account_ID, TThostFtdcBankIDType Bank_ID)
{
	CThostFtdcQryAccountregisterField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, Broker_ID);
	strcpy_s(req.AccountID, Account_ID);
	strcpy_s(req.BankID, Bank_ID);
	return pUserApi->ReqQryAccountregister(&req, ++iRequestID);
}
	///请求查询签约银行
TRADEAPI_API int ReqQryContractBank(TThostFtdcBrokerIDType Broker_ID,TThostFtdcBankIDType Bank_ID,	TThostFtdcBankBrchIDType BankBrch_ID)
{
	CThostFtdcQryContractBankField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,Broker_ID);
	if(Bank_ID != NULL)
		strcpy_s(req.BankID,Bank_ID);
	if(BankBrch_ID !=NULL)
		strcpy_s(req.BankBrchID,BankBrch_ID);
	return pUserApi->ReqQryContractBank(&req, ++iRequestID);
}
	///请求查询预埋单
TRADEAPI_API int ReqQryParkedOrder(TThostFtdcBrokerIDType BrokerID,TThostFtdcInvestorIDType InvestorID,TThostFtdcInstrumentIDType InstrumentID,TThostFtdcExchangeIDType ExchangeID)
{
	CThostFtdcQryParkedOrderField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,BrokerID);
	strcpy_s(req.InvestorID,InvestorID);
	if(InstrumentID != NULL)
		strcpy_s(req.InstrumentID,InstrumentID);
	if(ExchangeID != NULL)
		strcpy_s(req.ExchangeID,ExchangeID);
	return pUserApi->ReqQryParkedOrder(&req, ++iRequestID);
}
	///请求查询预埋撤单
TRADEAPI_API int ReqQryParkedOrderAction(TThostFtdcBrokerIDType BrokerID,TThostFtdcInvestorIDType InvestorID,TThostFtdcInstrumentIDType InstrumentID,TThostFtdcExchangeIDType ExchangeID)
{
	CThostFtdcQryParkedOrderActionField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID,BrokerID);
	strcpy_s(req.InvestorID,InvestorID);
	if(InstrumentID != NULL)
		strcpy_s(req.InstrumentID,InstrumentID);
	if(ExchangeID != NULL)
		strcpy_s(req.ExchangeID,ExchangeID);
	return pUserApi->ReqQryParkedOrderAction(&req, ++iRequestID);
}
	///期货发起银行资金转期货请求
TRADEAPI_API int ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *ReqTransfer)
{
	return pUserApi->ReqFromBankToFutureByFuture(ReqTransfer,++iRequestID);
}
	///期货发起期货资金转银行请求
TRADEAPI_API int ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *ReqTransfer)
{
	return pUserApi->ReqFromFutureToBankByFuture(ReqTransfer,++iRequestID);
}
	///期货发起查询银行余额请求
TRADEAPI_API int ReqQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *ReqQueryAccount)
{
	return pUserApi->ReqQueryBankAccountMoneyByFuture(ReqQueryAccount,++iRequestID);
}
//========================================
///==================================== 回调函数 =======================================
TRADEAPI_API void WINAPI RegOnFrontConnected(CBOnFrontConnected cb)		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
{	cbOnFrontConnected = cb;	}

TRADEAPI_API void WINAPI RegOnFrontDisconnected(CBOnFrontDisconnected cb)		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
{	cbOnFrontDisconnected = cb;	}

TRADEAPI_API void WINAPI RegOnHeartBeatWarning(CBOnHeartBeatWarning cb)		///心跳超时警告。当长时间未收到报文时，该方法被调用。
{	cbOnHeartBeatWarning = cb;	}

TRADEAPI_API void WINAPI RegRspUserLogin(CBRspUserLogin cb)	///登录请求响应
{cbRspUserLogin = cb; }
TRADEAPI_API void WINAPI RegRspUserLogout(CBRspUserLogout cb)	///登出请求响应
{cbRspUserLogout = cb; }
TRADEAPI_API void WINAPI RegRspUserPasswordUpdate(CBRspUserPasswordUpdate cb)	///用户口令更新请求响应
{cbRspUserPasswordUpdate = cb; }
TRADEAPI_API void WINAPI RegRspTradingAccountPasswordUpdate(CBRspTradingAccountPasswordUpdate cb)	///资金账户口令更新请求响应
{cbRspTradingAccountPasswordUpdate = cb; }
TRADEAPI_API void WINAPI RegRspOrderInsert(CBRspOrderInsert cb)	///报单录入请求响应
{cbRspOrderInsert = cb; }
TRADEAPI_API void WINAPI RegRspParkedOrderInsert(CBRspParkedOrderInsert cb)	///预埋单录入请求响应
{cbRspParkedOrderInsert = cb; }
TRADEAPI_API void WINAPI RegRspParkedOrderAction(CBRspParkedOrderAction cb)	///预埋撤单录入请求响应
{cbRspParkedOrderAction = cb; }
TRADEAPI_API void WINAPI RegRspOrderAction(CBRspOrderAction cb)	///报单操作请求响应
{cbRspOrderAction = cb; }
TRADEAPI_API void WINAPI RegRspQueryMaxOrderVolume(CBRspQueryMaxOrderVolume cb)	///查询最大报单数量响应
{cbRspQueryMaxOrderVolume = cb; }
TRADEAPI_API void WINAPI RegRspSettlementInfoConfirm(CBRspSettlementInfoConfirm cb)	///投资者结算结果确认响应
{cbRspSettlementInfoConfirm = cb; }
TRADEAPI_API void WINAPI RegRspRemoveParkedOrder(CBRspRemoveParkedOrder cb)	///删除预埋单响应
{cbRspRemoveParkedOrder = cb; }
TRADEAPI_API void WINAPI RegRspRemoveParkedOrderAction(CBRspRemoveParkedOrderAction cb)	///删除预埋撤单响应
{cbRspRemoveParkedOrderAction = cb; }
TRADEAPI_API void WINAPI RegRspQryOrder(CBRspQryOrder cb)	///请求查询报单响应
{cbRspQryOrder = cb; }
TRADEAPI_API void WINAPI RegRspQryTrade(CBRspQryTrade cb)	///请求查询成交响应
{cbRspQryTrade = cb; }
TRADEAPI_API void WINAPI RegRspQryInvestorPosition(CBRspQryInvestorPosition cb)	///请求查询投资者持仓响应
{cbRspQryInvestorPosition = cb; }
TRADEAPI_API void WINAPI RegRspQryTradingAccount(CBRspQryTradingAccount cb)	///请求查询资金账户响应
{cbRspQryTradingAccount = cb; }
TRADEAPI_API void WINAPI RegRspQryInvestor(CBRspQryInvestor cb)	///请求查询投资者响应
{cbRspQryInvestor = cb; }
TRADEAPI_API void WINAPI RegRspQryTradingCode(CBRspQryTradingCode cb)	///请求查询交易编码响应
{cbRspQryTradingCode = cb; }
TRADEAPI_API void WINAPI RegRspQryInstrumentMarginRate(CBRspQryInstrumentMarginRate cb)	///请求查询合约保证金率响应
{cbRspQryInstrumentMarginRate = cb; }
TRADEAPI_API void WINAPI RegRspQryInstrumentCommissionRate(CBRspQryInstrumentCommissionRate cb)	///请求查询合约手续费率响应
{cbRspQryInstrumentCommissionRate = cb; }
TRADEAPI_API void WINAPI RegRspQryExchange(CBRspQryExchange cb)	///请求查询交易所响应
{cbRspQryExchange = cb; }
TRADEAPI_API void WINAPI RegRspQryInstrument(CBRspQryInstrument cb)	///请求查询合约响应
{cbRspQryInstrument = cb; }
TRADEAPI_API void WINAPI RegRspQryDepthMarketData(CBRspQryDepthMarketData cb)	///请求查询行情响应
{cbRspQryDepthMarketData = cb; }
TRADEAPI_API void WINAPI RegRspQrySettlementInfo(CBRspQrySettlementInfo cb)	///请求查询投资者结算结果响应
{cbRspQrySettlementInfo = cb; }
TRADEAPI_API void WINAPI RegRspQryTransferBank(CBRspQryTransferBank cb)	///请求查询转帐银行响应
{cbRspQryTransferBank = cb; }
TRADEAPI_API void WINAPI RegRspQryInvestorPositionDetail(CBRspQryInvestorPositionDetail cb)	///请求查询投资者持仓明细响应
{cbRspQryInvestorPositionDetail = cb; }
TRADEAPI_API void WINAPI RegRspQryNotice(CBRspQryNotice cb)	///请求查询客户通知响应
{cbRspQryNotice = cb; }
TRADEAPI_API void WINAPI RegRspQrySettlementInfoConfirm(CBRspQrySettlementInfoConfirm cb)	///请求查询结算信息确认响应
{cbRspQrySettlementInfoConfirm = cb; }
TRADEAPI_API void WINAPI RegRspQryInvestorPositionCombineDetail(CBRspQryInvestorPositionCombineDetail cb)	///请求查询投资者持仓明细响应
{cbRspQryInvestorPositionCombineDetail = cb; }
TRADEAPI_API void WINAPI RegRspQryCFMMCTradingAccountKey(CBRspQryCFMMCTradingAccountKey cb)	///查询保证金监管系统经纪公司资金账户密钥响应
{cbRspQryCFMMCTradingAccountKey = cb; }
TRADEAPI_API void WINAPI RegRspQryTransferSerial(CBRspQryTransferSerial cb)	///请求查询转帐流水响应
{cbRspQryTransferSerial = cb; }
TRADEAPI_API void WINAPI RegRspQryAccountregister(CBRspQryAccountregister cb)	///请求查询银期签约关系响应
{
	cbRspQryAccountregister = cb;
}
TRADEAPI_API void WINAPI RegRspError(CBRspError cb)	///错误应答
{cbRspError = cb; }
TRADEAPI_API void WINAPI RegRtnOrder(CBRtnOrder cb)	///报单通知
{cbRtnOrder = cb; }
TRADEAPI_API void WINAPI RegRtnTrade(CBRtnTrade cb)	///成交通知
{cbRtnTrade = cb; }
TRADEAPI_API void WINAPI RegErrRtnOrderInsert(CBErrRtnOrderInsert cb)	///报单录入错误回报
{cbErrRtnOrderInsert = cb; }
TRADEAPI_API void WINAPI RegErrRtnOrderAction(CBErrRtnOrderAction cb)	///报单操作错误回报
{cbErrRtnOrderAction = cb; }
TRADEAPI_API void WINAPI RegRtnInstrumentStatus(CBRtnInstrumentStatus cb)	///合约交易状态通知
{cbRtnInstrumentStatus = cb; }
TRADEAPI_API void WINAPI RegRtnTradingNotice(CBRtnTradingNotice cb)	///交易通知
{cbRtnTradingNotice = cb; }
TRADEAPI_API void WINAPI RegRtnErrorConditionalOrder(CBRtnErrorConditionalOrder cb)	///提示条件单校验错误
{cbRtnErrorConditionalOrder = cb; }
TRADEAPI_API void WINAPI RegRspQryContractBank(CBRspQryContractBank cb)	///请求查询签约银行响应
{cbRspQryContractBank = cb; }
TRADEAPI_API void WINAPI RegRspQryParkedOrder(CBRspQryParkedOrder cb)	///请求查询预埋单响应
{cbRspQryParkedOrder = cb; }
TRADEAPI_API void WINAPI RegRspQryParkedOrderAction(CBRspQryParkedOrderAction cb)	///请求查询预埋撤单响应
{cbRspQryParkedOrderAction = cb; }
TRADEAPI_API void WINAPI RegRspQryTradingNotice(CBRspQryTradingNotice cb)	///请求查询交易通知响应
{cbRspQryTradingNotice = cb; }
TRADEAPI_API void WINAPI RegRspQryBrokerTradingParams(CBRspQryBrokerTradingParams cb)	///请求查询经纪公司交易参数响应
{cbRspQryBrokerTradingParams = cb; }
TRADEAPI_API void WINAPI RegRspQryBrokerTradingAlgos(CBRspQryBrokerTradingAlgos cb)	///请求查询经纪公司交易算法响应
{cbRspQryBrokerTradingAlgos = cb; }
TRADEAPI_API void WINAPI RegRtnFromBankToFutureByBank(CBRtnFromBankToFutureByBank cb)	///银行发起银行资金转期货通知
{cbRtnFromBankToFutureByBank = cb; }
TRADEAPI_API void WINAPI RegRtnFromFutureToBankByBank(CBRtnFromFutureToBankByBank cb)	///银行发起期货资金转银行通知
{cbRtnFromFutureToBankByBank = cb; }
TRADEAPI_API void WINAPI RegRtnRepealFromBankToFutureByBank(CBRtnRepealFromBankToFutureByBank cb)	///银行发起冲正银行转期货通知
{cbRtnRepealFromBankToFutureByBank = cb; }
TRADEAPI_API void WINAPI RegRtnRepealFromFutureToBankByBank(CBRtnRepealFromFutureToBankByBank cb)	///银行发起冲正期货转银行通知
{cbRtnRepealFromFutureToBankByBank = cb; }
TRADEAPI_API void WINAPI RegRtnFromBankToFutureByFuture(CBRtnFromBankToFutureByFuture cb)	///期货发起银行资金转期货通知
{cbRtnFromBankToFutureByFuture = cb; }
TRADEAPI_API void WINAPI RegRtnFromFutureToBankByFuture(CBRtnFromFutureToBankByFuture cb)	///期货发起期货资金转银行通知
{cbRtnFromFutureToBankByFuture = cb; }
TRADEAPI_API void WINAPI RegRtnRepealFromBankToFutureByFutureManual(CBRtnRepealFromBankToFutureByFutureManual cb)	///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
{cbRtnRepealFromBankToFutureByFutureManual = cb; }
TRADEAPI_API void WINAPI RegRtnRepealFromFutureToBankByFutureManual(CBRtnRepealFromFutureToBankByFutureManual cb)	///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
{cbRtnRepealFromFutureToBankByFutureManual = cb; }
TRADEAPI_API void WINAPI RegRtnQueryBankBalanceByFuture(CBRtnQueryBankBalanceByFuture cb)	///期货发起查询银行余额通知
{cbRtnQueryBankBalanceByFuture = cb; }
TRADEAPI_API void WINAPI RegErrRtnBankToFutureByFuture(CBErrRtnBankToFutureByFuture cb)	///期货发起银行资金转期货错误回报
{cbErrRtnBankToFutureByFuture = cb; }
TRADEAPI_API void WINAPI RegErrRtnFutureToBankByFuture(CBErrRtnFutureToBankByFuture cb)	///期货发起期货资金转银行错误回报
{cbErrRtnFutureToBankByFuture = cb; }
TRADEAPI_API void WINAPI RegErrRtnRepealBankToFutureByFutureManual(CBErrRtnRepealBankToFutureByFutureManual cb)	///系统运行时期货端手工发起冲正银行转期货错误回报
{cbErrRtnRepealBankToFutureByFutureManual = cb; }
TRADEAPI_API void WINAPI RegErrRtnRepealFutureToBankByFutureManual(CBErrRtnRepealFutureToBankByFutureManual cb)	///系统运行时期货端手工发起冲正期货转银行错误回报
{cbErrRtnRepealFutureToBankByFutureManual = cb; }
TRADEAPI_API void WINAPI RegErrRtnQueryBankBalanceByFuture(CBErrRtnQueryBankBalanceByFuture cb)	///期货发起查询银行余额错误回报
{cbErrRtnQueryBankBalanceByFuture = cb; }
TRADEAPI_API void WINAPI RegRtnRepealFromBankToFutureByFuture(CBRtnRepealFromBankToFutureByFuture cb)	///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
{cbRtnRepealFromBankToFutureByFuture = cb; }
TRADEAPI_API void WINAPI RegRtnRepealFromFutureToBankByFuture(CBRtnRepealFromFutureToBankByFuture cb)	///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
{cbRtnRepealFromFutureToBankByFuture = cb; }
TRADEAPI_API void WINAPI RegRspFromBankToFutureByFuture(CBRspFromBankToFutureByFuture cb)	///期货发起银行资金转期货应答
{cbRspFromBankToFutureByFuture = cb; }
TRADEAPI_API void WINAPI RegRspFromFutureToBankByFuture(CBRspFromFutureToBankByFuture cb)	///期货发起期货资金转银行应答
{cbRspFromFutureToBankByFuture = cb; }
TRADEAPI_API void WINAPI RegRspQueryBankAccountMoneyByFuture(CBRspQueryBankAccountMoneyByFuture cb)	///期货发起查询银行余额应答
{cbRspQueryBankAccountMoneyByFuture = cb; }
