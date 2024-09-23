-- Index (Non - Clustered Index)
-- 색인 : 책에서 맨 뒤에 나오는 목차?
-- > B-트리(이진탐색트리)로 이루어진 목차

-- 탐색 속도 : 클러스터인덱스에 비해 느림, 인덱스X(N), 인덱스(LogN)
-- 테이블에서 여러개 존재할 수 있음.

-- Clustered Index
-- 색인... 제일 좋은 색인
-- => 사전 그 자체
-- 기본키

-- 탐색 속도 : 빠름
-- 테이블에서 단 하나만 존재할 수 있음.

-- 알고리즘 고득점 Kit -> Heap -> 더 맵게
-- SQL 고득점 Kit -> Group by -> 조건에 맞는 사용자와 총 거래금액 조회하기

USE GameDB;

SELECT * FROM PlayerAccount;

ALTER TABLE PlayerAccount
DROP CONSTRAINT PK_account;

DROP INDEX PlayerAccount.index_1;

CREATE INDEX index_1 ON PlayerAccount(accountName);

-- 클러스터형 인덱스 만들기
CREATE CLUSTERED INDEX cIndex_1 ON PlayerAccount(accountName);

-- Primary Key 등록
ALTER TABLE PlayerAccount
ADD CONSTRAINT PK_AccountID PRIMARY KEY (accountID);