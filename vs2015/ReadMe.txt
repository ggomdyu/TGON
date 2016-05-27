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

[Attention]
- Abstract class의 member function은 플랫폼 비종속적인 코드가 들어가야 합니다.
만약 static member이면서 empty function인 경우 '__FUNCTION__ has not been implemented.' 
로그를 출력하는 코드를 작성하세요.
