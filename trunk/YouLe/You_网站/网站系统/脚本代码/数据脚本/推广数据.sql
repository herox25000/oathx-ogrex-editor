USE QPTreasureDB
GO

-- ��ʼ���ƹ�����
TRUNCATE TABLE GlobalSpreadInfo
GO

INSERT INTO GlobalSpreadInfo(RegisterGrantScore,PlayTimeCount,PlayTimeGrantScore,FillGrantRate,BalanceRate,MinBalanceScore) 
VALUES(1888,108000,100000,0.1,0.1,200000)

GO