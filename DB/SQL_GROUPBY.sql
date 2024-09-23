-- 집계함수
-- GROUP BY
-- HAVING

-- FROM
-- WHERE
-- GROUP BY
-- HAVING : GROUP BY 후 생긴 테이블에 한에서 조건절
-- SELECT
-- ORDER BY

-- players테이블에서 출신이 명확한 야구선수들의 고향에 따라서 몇명이 있는지 출력해라

-- SubQuery

SELECT *
FROM players
WHERE birthCountry IS NOT NULL
GROUP BY birthCountry

SELECT*
FROM players;

SELECT birthCountry, COUNT(lahmanID) AS playerCount
FROM players
WHERE birthCountry IS NOT NULL
GROUP BY birthCountry
HAVING COUNT(lahmanID) > 10 
ORDER BY playerCount DESC

-- batting 테이블에서 연도에 상관없이 팀별로 홈런을 친 개수대로 출력해주세요
-- 이 때 내림차순으로 정렬해주세요.
SELECT *
FROM batting

SELECT teamID, SUM(HR)
FROM batting
GROUP BY teamID
ORDER BY SUM(HR) DESC

-- batting 테이블에서  최대로 많은 수의 홈런을 기록한 팀과 홈런 개수를 출력
-- 이 때 최대 홈런을 친 playerID를 출력하라
SELECT *
FROM batting
WHERE HR = 
(
	SELECT TOP(1) MAX(HR)
	FROM batting
	GROUP BY teamID
	ORDER BY MAX(HR) DESC
)


-- GROUP BY
-- 고양이와 개는 몇마리 있을까
-- 동명 동물 수 찾기
-- 입양 시각 구하기
-- 가격대 별 상품 개수 구하기
-- 진료과별 총 예약 횟수 출력하기
-- 자동차 종류 별 특정 옵션이 포함된 자동차 수 구하기