
-- GameDB에
-- ItemTable 추가
-- 컬럼은 ItemID(INT, PK), ItemName(VARCHAR), ItemType, ItemPrice
-- 레코드는 개수는 5개 이상

-- SELELCT ->서울에 위치한 식당 목록 출력하기

-- SQL : 질의
-- COMMAND

CREATE DATABASE GameDB;

USE GameDB;

-- CREATE Table
-- Table Schema
CREATE TABLE PlayerAccount
(
	accountID INTEGER NOT NULL,
	accountName VARCHAR(10) NOT NULL,
	accountMoney INTEGER DEFAULT 0,
	accountCreateTime DATETIME,
	-- accountDeleteFlag VARCHAR(10)
	--(accountID) -- 제약, CONSTRAINT
);

SELECT * FROM PlayerAccount;

DROP TABLE PlayerAccount;

-- ALTER Column
ALTER TABLE PlayerAccount
ADD accountPassword INTEGER NOT NULL;

-- ADD CONSTRAINT
ALTER TABLE PlayerAccount
ADD CONSTRAINT PK_accountName PRIMARY KEY (accountName);

ALTER TABLE PlayerAccount
ADD CONSTRAINT PK_account PRIMARY KEY (accountID, accountName);

ALTER TABLE PlayerAccount
DROP CONSTRAINT PK_accountName;







-- 레코드(Row)용
-- 레코드 삽입
INSERT INTO PlayerAccount(accountID, accountName, accountMoney, accountCreateTime)
VALUES (3, 'Hanil', 1000000, NULL);

INSERT INTO PlayerAccount(accountID, accountName, accountMoney, accountCreateTime)
VALUES (2, 'Hanil2', 100000, NULL);

DELETE 
FROM PlayerAccount -- DELETE FROM ... : All Delete
WHERE accountID = 2

UPDATE PlayerAccount
SET accountName = 'Hanil123'
WHERE accountName = 'Hanil';

USE GameDB;
SELECT *
FROM PlayerAccount;

USE BaseballData;
SELECT *
FROM dbo.salaries;