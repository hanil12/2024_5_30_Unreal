-- DATABASE가 무엇인지
-- DATABASE를 왜 쓰는지
-- DATABASE에서 관계형 DB는 무엇인지

-- 기본키가 무엇인지
-- 인덱스...PK(클러스터형)... 클러스터형이 무엇인지 조사해오기
-- 어떤 자료구조로 구성이 되어있는지 []

-- FROM
-- WHERE
-- SELECT
-- ORDER BY

-- * : Allㅎ
-- ASC : 오름차순 ASCENDING의 약자
-- DESC : 내림차순 DESCENGING의 약자
SELECT *
FROM dbo.Customers;

SELECT *
FROM dbo.Customers
WHERE FirstName = 'Adam' AND MiddleInitial IS NULL;

SELECT TOP(100) FirstName
FROM dbo.Customers;

SELECT *
FROM dbo.Products
ORDER BY Price DESC;

-- SELECT
-- 모든 레코드 조회하기
-- 동물의 아이디와 이름
-- 조건에 맞는 회원수 구하기
-- 어린동물찾기
-- 아픈동물찾기
-- 역순 정렬하기
-- 상위 n개 레코드