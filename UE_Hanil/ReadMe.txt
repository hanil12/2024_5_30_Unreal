24 - 07 - 22
-  언리얼5
-- 게임엔진들은 영화촬영에 비유할 수가 있다.
 => 세트장 : 월드
 => 배우 :  Actor

- 언리얼은 상속구조와 컴포넌트 패턴이 핵심 철학.
-- 언리얼의 모든 오브젝트들은  UObject를 상속받아 만들어진다.
... 앞에 U가 붙으면 UOjbect를 상속받았다는 컨벤션이다.
... Actor만 제외. 그리고  Actor를 상속받는 자식들은 앞에 A가 붙는다.
... F가 붙으면 UObject를 상속받은 객체가 아니다.

-  동적할당
-- Actor => SpwanActor
-- Component => CreateDefaultSubObject

- 충돌
-- Block
-- Overlap
-- Ignore
