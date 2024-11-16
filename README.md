# Estação Meteorológica com Arduino

Este projeto consiste no desenvolvimento de uma **estação meteorológica utilizando Arduino**, com sensores para medir temperatura, umidade, pressão atmosférica, luminosidade e altitude. O objetivo é criar um sistema didático e funcional para monitoramento climático com exibição de dados em um LCD.

Este foi o **projeto final do 1º semestre do curso de Engenharia** no Insper, desenvolvido para a disciplina de **Instrumentação e Medição**.

## Funcionalidades

- Medição de:
  - **Temperatura** (Sensor LM35)
  - **Umidade** (Sensor DHT22)
  - **Pressão atmosférica** (Sensor BMP280)
  - **Luminosidade** (Sensor LDR)
  - **Altitude** (Sensor BMP280)
- Exibição dos dados em um display LCD 16x2.
- Ajustes de calibração para maior precisão das leituras.
- Rolar texto no LCD para exibir informações completas.

## Estrutura do Projeto

- **Hardware**:
  - Arduino Uno
  - Sensor LM35
  - Sensor DHT22
  - Sensor BMP280
  - Sensor LDR
  - Display LCD 16x2 com módulo I2C
  - Protoboard e jumpers

- **Software**:
  - Código escrito em C++ utilizando a extensão `.ino` para Arduino IDE.
  - Calibrações detalhadas implementadas para os sensores.

## Calibrações

As calibrações para os sensores foram realizadas com base em dados experimentais e ajustadas para maior precisão. 

**Importante**: Os valores apresentados foram obtidos para **os experimentos realizados neste projeto** e podem variar de acordo com diferentes fatores, como as condições ambientais, os sensores utilizados e o equipamento. 

Se você deseja obter maior precisão nos dados para sua aplicação, pode realizar as **calibrações personalizadas** seguindo o passo a passo descrito no [relatório completo](#relatório).

### Ajustes realizados:

1. **LM35**: Fórmula ajustada para compensar pequenos desvios no sensor analógico:
   Temperatura (ºC) = 98.29368086 * tensão (V) + 0.029367031

2. **DHT22**: Ajuste da umidade para maior precisão:
   Umidade (%) ajustada = 1.232 * umidade lida - 13.169

3. **BMP280**:
   - Pressão convertida para **hPa** com duas casas decimais.
   - Altitude calculada considerando a pressão do nível do mar (1013,25 hPa).

Os detalhes completos das calibrações e das medições podem ser encontrados no [relatório completo](#relatório).

## Instalação e Uso

1. **Clone o repositório**:
   ```bash
   git clone https://github.com/MicaeleGomes/estacao-meteorologica-arduino.git
   cd estacao-meteorologica-arduino

2. Abra o arquivo no Arduino IDE:
   -  Certifique-se de que o nome do arquivo `.ino` corresponde à pasta do projeto.

3. Faça o upload para o Arduino:
   -  Conecte o Arduino ao computador.
   -  Carregue o código na placa utilizando o Arduino IDE.

4. Monte o hardware:
   -   Siga o esquema de conexão descrito no relatório disponível nesse repositório.

5. Visualize os dados no LCD:
   -  Ligue o Arduino com o hardware montado e observe as leituras no display.

## Relatório Completo

O relatório com todas as calibrações, ajustes, e explicações detalhadas sobre a montagem está disponível neste repositório:

- [Relatório Completo (PDF)](./relatorio-estacao-meteorologica.pdf)

## Vídeo de Apresentação

Assista ao vídeo demonstrativo da estação meteorológica em funcionamento:
[![Vídeo de Apresentação](https://img.youtube.com/vi/SEU_VIDEO_ID/0.jpg)](https://www.youtube.com/watch?v=SEU_VIDEO_ID)

## Autor

Desenvolvido por **Micaele Gomes**, estudante de Engenharia no Insper. Este projeto foi parte da disciplina de **Instrumentação e Medição**, com objetivo de aplicar conhecimentos sobre sensores e sistemas de medição.

## Licença

Este projeto está licenciado sob a licença MIT. Veja o arquivo [LICENSE](./LICENSE) para mais detalhes.
