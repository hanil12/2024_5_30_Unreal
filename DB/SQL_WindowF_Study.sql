SELECT TOP (1000) [yearID]
      ,[teamID]
      ,[lgID]
      ,[playerID]
      ,[salary]
  FROM [BaseballData].[dbo].[salaries]


USE BaseballData;
-- 윈도우 함수

SELECT *
FROM salaries;

--           서브셋               범위
-- ~ OVER([PARTITION] [ORDER BY] [ROWS])

-- 전체 데이터를 연봉 순서로 나열하고, 순위 표기
SELECT *,
	ROW_NUMBER() OVER (ORDER BY salary DESC),
	RANK() OVER (ORDER BY salary DESC),
	DENSE_RANK() OVER (ORDER BY salary DESC),
	NTILE(100) OVER (ORDER BY salary DESC)
FROM salaries;


-- playerID 별 순위를 따로 하고 싶다
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
-- ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW 범위
SELECT *,
	RANK() OVER (PARTITION BY playerID ORDER BY salary DESC),
	FIRST_VALUE(salary) OVER (PARTITION BY playerID 
								ORDER BY salary DESC
								ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS BEST,
	LAST_VALUE(salary) OVER (PARTITION BY playerID
							 ORDER BY salary DESC
							 ROWS BETWEEN CURRENT ROW AND UNBOUNDED FOLLOWING) AS WORST
FROM salaries
ORDER BY playerID;