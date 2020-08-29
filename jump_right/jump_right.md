# jump_right

아마도 동적 디버거를 사용해야 했을 문제였을 것입니다. 먼저 success에 해당하는 함수 주소를 구하고, offset을 더해서 해당 값으로 점프하는 로직을 만나기 이전 bp를 걸어 주소를 확인하거나, 0을 입력해 값을 더하기 전 주소가 무엇인지 확인합니다. 이후 success 주소외 구한 주소의 차를 md5하면 됩니다.

여담입니다만, md5에 대해서 궁금하신 분들은 구글링을 통해 찾아보시면 좋고, 일반적으로 바뀌지 않는 code section을 보호하기 위한 기법인 PIE에 대해서 알아보셔도 많은 도움이 될 것입니다.