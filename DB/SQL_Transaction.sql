
-- Transaction : 트랙젝션
-- 더 이상 분할이 불가능한 업무처리의 단위
-- => 한꺼번에 수행되어야할 일련의 연산 모음
-- => 원자성(atomic), 원자적으로 실행되어야하는 작업

SELECT * FROM PlayerAccount;

-- 거래
-- 한일의 템을 제거
-- 한일의 돈이 추가

-- 도훈 템이 추가
-- 도훈의 돈이 제거 ... 실패

-- ALL OR NOTHING

-- BEGIN TRAN
-- COMMIT
-- ROLLBACK

-- 트랜잭션 안에는 항상 원자적으로 실행되야하는 코드만 와야한다.
-- => Lock을 짧게 써야하는 코드, 진짜로 원자적으로 실행되어야하는 코드

INSERT INTO PlayerAccount VALUES (3, 'hanil3', 3000, GETUTCDATE());

SELECT * FROM PlayerAccount;

BEGIN TRAN
INSERT INTO PlayerAccount VALUES (5, 'hanil5', 5000, GETUTCDATE());
ROLLBACK;

BEGIN TRAN
INSERT INTO PlayerAccount VALUES (6, 'hanil6', 6000, GETUTCDATE());
COMMIT;

-- 응용
-- TRY CATCH
BEGIN TRY
	BEGIN TRAN;
		INSERT INTO PlayerAccount VALUES (1,'dohun', 20000, GETUTCDATE());
		INSERT INTO PlayerAccount VALUES (7,'hanil7', 20000, GETUTCDATE());
	COMMIT;
		-- ALL
END TRY
BEGIN CATCH
	IF @@TRANCOUNT > 0 -- 현재 활성화 된 트랜잭션의 수를 반환
		ROLLBACK
		-- NOTHING
END CATCH
