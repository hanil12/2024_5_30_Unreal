USE pubs;

SELECT *
FROM dbo.employee
WHERE emp_id = 'L-B31947F';

CREATE TABLE Test
(
	EmployeeID  NVARCHAR(20) NOT NULL,
	fName	    NVARCHAR(20) NULL,
	minit       NVARCHAR(20) NULL,
	hire_data   DATETIME NULL
);
GO

INSERT INTO Test
SELECT emp_id, fname, minit, hire_date
FROM employee;

SELECT * FROM employee;

SELECT * FROM Test;

-- 넌클러스터형 인덱스 추가
CREATE INDEX Test_Index ON Test(fname);

-- 클러스터형 인덱스 추가
CREATE CLUSTERED INDEX Test_CIndex ON Test(EmployeeID);

DROP INDEX Test_Index ON Test;

SELECT index_id, name
FROM sys.indexes
WHERE object_id = object_id('Test');

-- 728
-- 클러스터형 인덱스가 넌클러스터형 인덱스에 영향을 미치고 있다.
DBCC IND('pubs', 'Test',1);

DBCC PAGE('pubs', 1, 744, 3);