# Proyecto de Computacion Grafica. Semestre 2021-1
**Facultad de Ingenieria UNAM**
**Ivan Marin Roldan**

# Vision General (Overview)

Este Proyecto se realizo como parte de la materia de Computacion Grafica para el semestre 2020-1.

Se trata de una animación de una letra **'W'** que cae y hace el efecto de rebotar.

# Como ejecutar el proyecto (installation)

## Pre-requisitos

Este proyecto fue creado con OpenGL 3.7 beta y Visual Studio Comunity 2017. Para configurar su entorno de desarrollo, por favor, siga las instrucciones disponibles en el siguiente [tutorial](https://www.absingh.com/opengl/)

## Configuracion adicional
Para poder compilar el proyecto en modo *Release* se debe realizar una configuracion adicional. En Visual Studio:

* Vaya a *Proyecto > propiedades*
* Seleccione *Propiedades de configuracion* en el panel izquierdo
* Seleccione *Vinculador*
* Seleccione *Avanzadas*
* En el panel derecho, seleccione la ultima opcion llamada *La imagen tiene controladores de excepciones seguros*
* Cambie el valor a **NO**
* De clic en *Aceptar*

El proyecto deberia compilar en la configuracion *Release*

## Agregar archivo de codigo a la solucion

En el tutorial anterior, queda configurado un proyecto, en el que se puede agregar el archivo _'Proyecto_2021_CG.cpp'_ que contiene la funcion main y la logica del programa completo.

A partir de este punto, sientase libre de compilar y ejecutar el proyecto para poder visualizar la animacion.

# Uso del programa (usage)

Una vez que el programa se pone en ejecucion, se mostrara la letra **'W'** en una posicion fija. Para reproducir la animacion, presione la tecla *'espacio'* y la animacion empezara su curso.

# Licencia (License)

Este proyecto cuenta con la licencia de MIT
