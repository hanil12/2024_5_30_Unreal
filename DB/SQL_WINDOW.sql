USE BaseballData;

-- 과제
-- 넌 클러스터드형 인덱스
-- HeapTable...?
-- RID...?
-- 클러스터드형 인덱스
-- 클러스터드형 인덱스가 생기면 HeapTable은 어떻게되는지

-- Index Scan과 Index Seek의 차이
-- KEY LOOK UP 과 RID LOOK UP이 무엇인지


-- WINDOW 함수

SELECT *
FROM salaries
ORDER BY salary DESC, playerID;

SELECT playerID, SUM(salary)
FROM dbo.salaries
GROUP BY playerID
ORDER BY SUM(salary) DESC;


--          서브셋       정렬     범위
-- ~ OVER([PARTITION] [ORDER BY] [ROWS])

-- 전체 데이터를 연봉 순서대로 나열하고, 순위를 표기하고 싶다.
SELECT *,
	ROW_NUMBER() OVER(ORDER BY salary DESC),
	RANK() OVER (ORDER BY salary DESC),
	DENSE_RANK() OVER (ORDER BY salary DESC),
	NTILE(100) OVER (ORDER BY salary DESC) -- 백분위 표시
FROM salaries;

-- playerID 별 순위를 따로 하고 싶은 경우
SELECT *,
	RANK() OVER (PARTITION BY playerID ORDER BY salary DESC)
FROM salaries
ORDER BY playerID;


-- LAG(바로 이전), LEAD(바로 다음)
SELECT *,
	RANK() OVER (PARTITION BY playerID ORDER BY salary DESC),
	LAG(salary) OVER (PARTITION BY playerID ORDER BY salary DESC) AS PREV,
	LEAD(salary) OVER (PARTITION BY playerID ORDER BY salary DESC) AS NEXT
FROM salaries
ORDER BY playerID;

-- FIRST_VALUE, LAST_VALUE(범위)
-- 
SELECT *,
	RANK() OVER (PARTITION BY playerID ORDER BY salary DESC) AS RANK,

	FIRST_VALUE(salary) OVER(
	PARTITION BY playerID ORDER BY salary DESC
	ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS MAX_SALARY,

	LAST_VALUE(salary) OVER
	(PARTITION BY playerID ORDER BY salary DESC
	ROWS BETWEEN CURRENT ROW AND UNBOUNDED FOLLOWING) AS MIN_SALARY
FROM salaries
ORDER BY playerID, RANK;