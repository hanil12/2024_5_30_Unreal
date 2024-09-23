USE BaseballData;

-- 완전탐색 -> 전력망을 둘로 나누기
-- Join -> 보호소에서 중성화한 동물

-- SQL에서 변수 선언 및 정의
DECLARE @i AS INT = 10;
DECLARE @s AS NVARCHAR(15);

SET @i = 44;
SET @s = 'hi';

SELECT * 
FROM batting
WHERE batting.HR >= @i;

-- s를 players에서 몸무게가 가장 많이 나가는 player의 이름으로 세팅해주세요.
SET @s = 
(
SELECT TOP(1) (nameFirst + ' ' + nameLast) as fullName
FROM players
ORDER BY players.weight DESC
)

SELECT @s;

-- 임시 테이블
DECLARE @test TABLE
(
	fullName VARCHAR(50) NOT NULL,
	playerWeight INT NOT NULL
)

INSERT INTO @test VALUES('temp', 100);

-- 새로운 테이블을 만들고 temp
-- 컬럼명(fullName, salary)
-- name.. [players] / salary .. [salaries]

INSERT INTO @test
SELECT (nameFirst + ' ' + nameLast), salary
FROM players AS P
LEFT JOIN salaries AS S
ON P.playerID = S.playerID
WHERE S.salary IS NOT NULL

SELECT * FROM @test;

-- 분기문
 -- batch : 하나의 묶음으로 분석되고 실행되는 명령어 집합. 일괄 처리 실행
 GO 

DECLARE @i AS INT = 10;

-- IF 문
IF @i = 10
BEGIN
PRINT('TRUE');
PRINT('TRUE');
END
ELSE
PRINT('FALSE');

GO
DECLARE @i AS INT = 0;
WHILE @i < 10
BEGIN

	SET @i = @i + 1;

	IF @i = 3 BREAK;
	PRINT @i;
END