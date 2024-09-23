USE BaseballData;

SELECT* FROM dbo.players;

-- FROM
-- WHERE
-- SELECT
-- ORDER BY

-- DATE TIME
-- Players 테이블에서 모든 사람의 이름과 태어난 날짜, 사망 날짜를 추출해주세요.
-- 단 아직 살아있는 사람은 제외시켜주세요.
SELECT nameFirst, nameLast, 
DATEFROMPARTS(birthYear, birthMonth, birthDay) as 생일 ,
DATEFROMPARTS(deathYear, deathMonth, deathDay) as 사망날짜,
(deathYear - birthYear) as 생전나이
FROM players
WHERE deathYear IS NOT NULL AND DATEFROMPARTS(birthYear, birthMonth, birthDay) IS NOT NULL
ORDER BY 생전나이 DESC;

-- LIKE 'a%' : a로 시작하는 모든 문자열 포함
-- LIKE 'a_' : a 뒤에 어떤 문자열이 단 한글자만 오는 것 허용
SELECT DISTINCT birthCity 
FROM players
WHERE birthCity LIKE 'New_____'; -- '%' wildCard

-- 집계함수, Aggregate Function => Group By, Having
-- MIN
-- MAX
-- COUNT
-- SUM
-- AVG

-- 프로그래머스 문제 (SUM, MAX, MIN)
-- 가장 비싼 상품 구하기
-- 가격이 제일 비싼 식품의 정보 출력하기
-- 최대값 구하기
-- 동물 수 구하기
-- 중복 제거하기

SELECT *
FROM players;
