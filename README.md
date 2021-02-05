# Proyecto de Computacion Grafica. Semestre 2021-1
**Facultad de Ingenieria UNAM**
**Ivan Marin Roldan**

# Vision General (Overview)

Este Proyecto se realizo como parte de la materia de Computacion Grafica para el semestre 2021-1.

Se trata de una animación de una letra **'W'** que cae y hace el efecto de rebotar.

El contexto que se le da es el de una casa, donde la W Forma parte de la leyenda "Welcome Home".

# Como ejecutar el proyecto (Installation)

## Pre-requisitos

Este proyecto fue creado con OpenGL 3.7 beta y Visual Studio Comunity 2017. Para configurar su entorno de desarrollo, por favor, siga las siguientes instrucciones:

1. Descargue las bibliotecas de GLUT desde la [página de OpenGL](https://www.opengl.org/resources/libraries/glut/glutdlls37beta.zip)
2. Descomprima el archivo .zip descargado en el paso anterior en una ubicación conocida para usted. Por ejemplo: *'Descargas'*
3. Copie el archivo `glut.h` en `C:\Program Files(x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\{numero de version}\include\GL`

 Es posible que la carpeta _GL_ no exista en la ubicación especificada, de ser así, créela usted mismo(a). {numero de version} puede variar en su sistema.

4. Copie el archivo `glut.lib` en `C:\Program Files(x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\{numero de version}\lib\x64`
5. Copie el archivo `glut32.lib` en `C:\Program Files(x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\{numero de version}\lib\x86`
6. Copie los archivos `glut.dll` y `glut32.dll` en `C:\Windows\SysWOW64`
7. Copie el archivo `glut32.dll` en `C:\Windows\System32`

## Configuracion del proyecto en Visual Studio 2017

Para la configuracion del proyecto, siga los siguientes pasos:
1. Cree un nuevo proyecto: _Archivo > Nuevo > proyecto_
2. En el asistente de nuevo proyecto, seleccione del panel izquierdo _Visual C++ > Escritorio de Windows_
3. En el panel central seleccione `Aplicacion de consola`
4. De un nombre al proyecto y seleccione _Aceptar_
5. Una vez creado el proyecto, vaya a _Proyecto > Propiedades_
6. De la parte superior seleccione _Toda la configuracion_ del menú desplegable
7. En el panel izquierdo, seleccione _Propiedades de configuracion > C/C++ > Encabezados precompilados_ y cambie la opcion _Encabezado precompilado_ a _No utilizar encabezados precompilados_
8. En el panel izquierdo, seleccione _Propiedades de configuracion > Vinculador > Entrada_. En el panel derecho, seleccione _Dependencias adicionales > Editar_ y escriba:
   `opengl32.lib`
   `glu32.lib`
   `glut32.lib`
especificando cada archivo _.lib_ en una linea.

## Agregar archivos de codigo a la solucion

Una vez configurado el proyecto de Visual Studio, se puede agregar el archivo _'Proyecto_2021_CG.cpp'_ que contiene la funcion main y la logica del programa completo. Tambien debe agregar los archivos de texturas que se encuentran en la carpeta _'Proyecto_2021_CG/'_. Para agregar todos los archivos, en Visual Studio:

* Seleccione _'Proyecto > Agregar elemento existente'_
* En la ventana que se muestra seleccione todos los archivos con extension *.cpp* que se encuentran en la carpeta _'Proyecto_2021_CG/'_
* De clic en *'Agregar'*

## Configuracion adicional
Para poder compilar el proyecto en modo *Release* se debe realizar una configuracion adicional. En Visual Studio:

* Vaya a *'Proyecto > propiedades'*
* Seleccione *Propiedades de configuracion > Vinculador > Avanzadas* en el panel izquierdo
* En el panel derecho, seleccione la ultima opcion llamada *'La imagen tiene controladores de excepciones seguros'*
* Cambie el valor a **'NO'**
* De clic en *'Aceptar'*

El proyecto deberia compilar correctamente en la configuracion *'Release'*

_NOTA: Para la configuracion 'Debug' no se necesita hacer ningun ajuste adicional._

## Compilar y ejecutar

Para compilar el proyecto desde Visual Studio:
* Seleccione *'Compilar > Compilar solucion'*

Para Ejecutar el programa desde Visual Studio:
* Seleccione *'Depurar > Iniciar sin depurar'*

# Uso del programa (usage)

Una vez que el programa se pone en ejecucion, se mostrara la fachada de una casa con el letrero "Welcome Home" en una posicion fija. Para reproducir la animacion, presione la tecla *'Espacio'* y la animacion empezara su curso. La letra _W_ caera y, tras varios rebotes saldra de la vista. En cualquier momento, o hasta que termine la animacion, puede presionar la tecla _'R'_ para devolver la W a su estado inicial.

# Licencia (License)

Este proyecto cuenta con la licencia de [MIT](https://mit-license.org/)
