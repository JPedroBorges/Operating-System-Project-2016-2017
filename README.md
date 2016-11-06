# ProjectoSO2016-2017

## 1 Objetivos
O presente trabalho tem como objetivo a concepção e a implementação de um simulador de um Parque Aquático. Pretende-se assim que os alunos pratiquem os conceitos aprendidos nas aulas teóricas e práticas na concepção e desenvolvimento de um sistema simples, empregando os mecanismos de concorrência, sincronização e comunicação existentes na linguagem C

## 2 Descrição
O Parque Aquático a simular é composto de diferentes zonas de natação, mergulho, tobogãs, etc... (e.g., ver Parque Aquático de Santa Cruz).
Normalmente, cada espaço, por questões de segurança e políticas do Parque, tem diferentes regras de acesso. Alguns são de acesso livre a todos os utilizadores, outros apenas a utilizadores com específicos, e ainda, algumas restrições horárias.
Os utilizadores, após entrarem no Parque, vão para uma atração específica e podem movimentarse de atração em atração, ficando em cada uma um determinado tempo. No caso da zona estar lotada, o utilizador deverá esperar ou ir para outra zona ou ainda ir embora do Parque. Nesta simulação o utilizador deverá, pelo menos aceder (ou tentar) à maioria dos espaços.
A simulação a implementar pretende avaliar as condições de funcionamento de um equipamento deste género em termos de quantas pessoas pode servir, quais os tempos de espera médios, quantas desistem, entre outros.
As opções para a simulação são muitas e variadas e ficam à consideração de cada grupo, constituindo elemento de avaliação. Por exemplo: Qual o tamanho máximo da fila para uma das atrações? Qual o tipo de privilégios para alguns utilizadores? As pessoas chegam todas de uma vez ou vão chegando? O tempo numa determinada atração é sempre o mesmo? A abertura encerramento de atrações é relevante?

## 3 Arquitetura
O sistema a desenvolver deverá conter duas aplicações, a primeira (Simulador) que efetuará toda a simulação, e a segunda (Monitor) que receberá todas as mensagens enviadas pela primeira e fará todo o seu tratamento.
O **Simulador** deverá ser lançado tendo por parâmetro o ficheiro de configuração da simulação. Os dados que deverão estar presentes, no mínimo, para o início da simulação são os seguintes: tempo médio1 de chegada dos utilizadores e tempos diversos, dimensão dos recursos, probabilidade de desistência nas filas, início da simulação e tempo de simulação2. A Figura 1 apresenta a arquitetura de ficheiros para o projeto. Caso necessário podem ser indicados outros ficheiros (um ficheiro por cada tipo de relatório, apenas um ficheiro de configuração, e outros).
O **Simulador** deverá no seu arranque ligar-se ao **Monitor**. Durante a simulação devem ser apresentados alguns dados sobre o estado da simulação. Por exemplo:

>. . .

>Chegou um u t i l i z a d o r . Numero 234.

>O u t i l i z a d o r 123 entrou na zona A.

>O u t i l i z a d o r 136 entrou na zona B.

>O u t i l i z a d o r 129 d e s i s t i u .

>. . .

O **Simulador** deverá ter métodos para gerar aleatoriamente a chegada dos utilizadores (cada utilizador será um thread) aos recursos, que permitam a correta coordenação e sincronização dos utilizadores (por via de semáforos) e que enviem mensagens para o **Monitor** (comunicação via *sockets* – Unix ou Internet).
O Monitor aceita uma ligação de um Simulador e guarda em ficheiros todos os registos enviados por este. O tratamento dos dados da simulação acontece ao nível do **Monitor** (cálculo da média do tempo à espera, por exemplo). Durante o funcionamento do Monitor este deve apresentar dados sobre o seu estado de execução. Por exemplo:

>Estado actual => Simulacao a decorrer !
>U t i l i z a d o r e s : 123
>Desistencias : 15
>Tempo medio de espera :24 min .

1) Os tempos médios expressam o ritmo aproximado de um dado acontecimento e deve ser implementado um método aleatório para calcular os diversos tempos para diversas fases do projeto.
2) A temporização da simulação deve ser definida de forma a poder ser testada em poucos minutos. Aconselha-se a utilização do time stamp do unix e resumir os tempos da simulação a segundos.
Exemplo dos comandos para lançamento das aplicações:

$ monitor monitor . conf
$ simulador simulacao . conf

## 4 Estrutura de Dados
As duas aplicações terão um conjunto de estruturas de dados para guardar diversas informações. Para os ficheiros de configuração fica a seguinte sugestão:
>PARAMETRO1: dado1
>PARAMETRO2: dado2
. . .

onde ’PARAMETRO’ significa a designação do parâmetro e ’dado’ é o seu valor.
Os dados sobre os acontecimentos da simulação poderão ter o seguinte formato:

>I d U t i l i z a d o r hora Acontecimento
>. . .

onde o ’Acontecimento’3 pode ser, por exemplo, um dos seguintes: criação do utilizador,
chegada ao recursos, passagem em filas, entrada e saída dos recursos e desistência.
