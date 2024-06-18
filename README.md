# Projeto de Microcontroladores

## O projeto consiste em:
Aplicação alvo são tubulações de água de residências (individuais e de condomínios).
O local de aplicação é logo depois do registro da empresa provedora da água.
Interfaces de comunicação será pelo usuário através de dados captados pelos sensores em uma página web local, gerada pelo IP de um ESP32, onde dados são colocados lá para serem vistos 24 horas por dia.
Usaremos um microcontrolador PIC e 2 Sensores Ultrassônico JSN-SR04M, além de um ESP32 para envio dos dados.
Seu objetivo principal é ler os níveis da água e será colocado de maneira que ele detecte se a tubulação de fornecimento estará entupida ou vazando, mas não onde. Seu propósito é para impedir desperdício (e contas elevadas no final do mês) e possíveis transtornos com a falta de fornecimento durante o uso diário.
O dispositivo será montando com ambos os sensores perpendiculares a tubulação principal a uma certa distância um do outro e em uma altura ainda a decidir em testes.

___

### Requisitos funcionais
RF01: O sistema deve comunicar com o usuário através de uma página web;
RF02: Os sensores devem suportar umidades elevadas;
RF03: deve é alimentado por pela rede de energia;
RF04: Deve estar a todo momento conectado a algum roteador;
RD05: O sistema deve saber identificar quando há algum entupimento e avisar o usuário de alguma forma quando isso ocorre;
RD06: vai enviar os dados para uma página web através de um ESP32
RD07: o sistema deve observar continuamente o nível da água
RD08: o sistema irá reservar o histórico do sensor por 1 mês

___

### Requisitos não funcionais
RNF01: O dispositivo deve usar JSN-SR04M
RNF06: o sistema deve usar ESP32;
RNF02: o cabo de alimentação deve alimentar 5V no microcontrolador e o ESP;
RNF03: O microcontrolador será um PIC16877A;
RNF04: o protocolo de comunicação será UDP;
RNF05: o sistema deve enviar dados para a página web toda vez que ele detectar uma mudança no nível da água ou a cada 30 minutos;
RNF07: a pagina web será desenvolvida usando o framework flask do python
RNF08: a pagina web poderá ser acessada no ip de rede local na porta 5000