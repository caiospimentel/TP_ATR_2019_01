Para compilar o processo, contendo as threads process_thread e softPLC_thread, é necessário utilizar a seguinte linha de comando, de forma a incluir as bibliotecas a as funções de sincronização:

g++ local.cpp customLibraries.cpp -o local -std=c++11 -pthread

executando-a pela linha de comando:

./local xxxx

A seguir, deve ser aberta outra instância do terminal, e executar a linha abaixo para rodar o sistema supervisório:

g++ synoptic_process.cpp customLibraries.cpp -o synoptic_process -std=c++11 -pthread

que deve ser executada com:

./synoptic_process xxxx

Ressalta-se que xxxx é o número da porta selecionado. Deve ser o mesmo para os dois processos e ser maior que 1024

É importante notar que, para o bom funcionamento da conexão TCP, o servidor, presente no processo sinóptico, deve rodar primeiro
