Para compilar o processo, contendo as threads process_thread e softPLC_thread, é necessário utilizar a seguinte linha de comando, de forma a incluir as bibliotecas a as funções de sincronização:

g++ local.cpp customLibraries.cpp -std=c++11 -pthread

A seguir, deve ser aberta outra instância do terminal, e executar a linha abaixo para rodar o sistema supervisório:

g++ synoptic_process.cpp customLibraries.cpp -std=c++11 -pthread


É importante notar que, para o bom funcionamento da conexão TCP, o servidor deve rodar primeiro
