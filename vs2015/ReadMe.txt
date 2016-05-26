#######################################
#
#	TGON project ReadMe
#
########################################


//
// 1. Naming
//

[Attention]
- 모든 클래스는 tgon 네임스페이스 안에 담겨있어야 합니다.


//
// 2. Platform class의 구조
//

[Q&A]
- T의 이름으로 시작하는 클래스는 무엇입니까?
Cross-platform을 위해 사용해야 할 클래스입니다.
Android..., Windows... 와 같은 플랫폼 종속적 클래스를 현재 플랫폼에 알맞게 선택합니다.

- Abstract의 이름으로 시작하는 클래스는 무엇입니까?
Cross-platform에서 인터페이스 또는 잠재적으로 오버로드될 함수를 나열합니다.


[Attention]
- Abstract class의 member function은 플랫폼 비종속적인 코드가 들어가야 합니다.
만약 static member이면서 empty function인 경우 '__FUNCTION__ has not been implemented.' 
로그를 출력하는 코드를 작성하세요.
