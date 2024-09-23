-- SubQuery

-- 기본키와 외래키에 대해서 조사
-- JOIN
-- -> 있었는데요 없었습니다.
-- -> 오랜 기간 보호한 동물
-- -> 그룹별 조건에 맞는 식당 목록 출력하기

-- players 테이블에서 birthYear가 1900 이상인 플레이어들의 이름을 추출해라
SELECT birthYear, nameFirst, nameLast
FROM players
WHERE birthYear >= 1900;

-- 방금 뽑은 위 데이터에서 성이 알파벳 A로 시작하는 사람들의 정보를 추출해라
SELECT *
FROM 
(
SELECT birthYear, nameFirst, nameLast
FROM players
WHERE birthYear >= 1900
) T0
WHERE T0.nameFirst LIKE 'A%';

-- players 테이블에서 가장 최근에 태어난 사람의 playerID와 birthYear와 이름을 출력하시오
SELECT TOP(1) playerID, birthYear, nameFirst, nameLast
FROM players
ORDER BY birthYear DESC;

-- 가장 최근에 태어난 사람의 이름과, 생일 년,월,일을 출력해주세요
SELECT nameFirst, nameLast, birthYear, birthMonth, birthDay
FROM players
WHERE playerID = 
(SELECT TOP(1) playerID
FROM players
ORDER BY birthYear DESC);

-- UNION
-- 관계형 데이터베이스

-- 생일이 1950년도 이상의 player의 모든 정보
(SELECT * FROM players
WHERE birthYear >= 1950)
UNION
(SELECT * FROM players
WHERE birthYear < 1900)

-- salaries 테이블에서 평균 연봉이 3,000,000 이상의 playerID 와 평균연봉 출력
SELECT playerID, AVG(salary) as 평균연봉
FROM salaries
GROUP BY playerID
HAVING AVG(salary) >= 3000000

-- players 테이블에서 12월에 태어난 선수
SELECT playerID, birthMonth
FROM players
WHERE  birthMonth = 12

-- 연봉이 30만 달러이상 이거나 12월에 태어난 선수의 playerID
SELECT playerID
FROM salaries
GROUP BY playerID
HAVING AVG(salary) >= 300000 AND playerID IS NOT NULL
UNION ALL -- 중복을 허용
SELECT playerID
FROM players
WHERE  birthMonth = 12 AND playerID IS NOT NULL
ORDER BY playerID

-- UNION : 중복이 있으면 자동으로 제거
-- UNION ALL : 중복허용

-- JOIN
-- CROSS JOIN
SELECT *
FROM
((SELECT TOP(100)* FROM players) T0
CROSS JOIN
(SELECT TOP(100)* FROM salaries) T1)

-- INNER JOIN : 가로로 합친다.
-- 두개의 테이블을 가로로 결합하고, 결합 기준은 ON (외래키)
-- playerID가 양쪽에 NULL이 아닌 얘들만 골라서 결합시킨다.
SELECT lahmanID, playerID, nameFirst, nameLast
FROM players

SELECT *
FROM salaries

SELECT lahmanID, pTable.playerID, nameFirst, nameLast, salary
FROM players AS pTable
INNER JOIN salaries AS sTable
ON pTable.playerID = sTable.playerID -- 외래키

-- OUTER JOIN (99퍼로 씀)
-- LEFT JOIN / RIGHT JOIN
-- LEFT JOIN
-- => playerID가 왼쪽에 있으면 무조건 표시, 이 때 오른쪽에 없으면 오른쪽 정보 무조건 NULL 표시
SELECT  lahmanID, pTable.playerID, nameFirst, nameLast, salary
FROM players AS pTable
LEFT JOIN salaries AS sTable
ON pTable.playerID = sTable.playerID;