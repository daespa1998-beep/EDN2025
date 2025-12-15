<<<<<<< HEAD
#primer taller - ordenamientos de algoritmos en C

+-ete programa maneja dos algoritmos de ordenamiento los cuales son:

---Selection Sort   asendente---
---Insertion Sort   desendente---

#descricion  del problema
+-programa de C que pide o captura 10 números int positivos que se organizan tanto de forma ascendente como descendente con insertión sort y muestre cada paso

#Ejemplos:

---Entradas---

+-digite un numero positivo, posicion 1:9
+-digite un numero positivo, posicion 2:1
+-digite un numero positivo, posicion 3:8
+-digite un numero positivo, posicion 4:2
+-digite un numero positivo, posicion 5:7
+-digite un numero positivo, posicion 6:3
+-digite un numero positivo, posicion 7:6
+-digite un numero positivo, posicion 8:4
+-digite un numero positivo, posicion 9:5
+-digite un numero positivo, posicion 10:25


---Arreglo original---

9 1 8 2 7 3 6 4 5 25 

---Ascendente  con Selection Sort---
+-Paso 1: 1 9 8 2 7 3 6 4 5 25
+-Paso 2: 1 2 8 9 7 3 6 4 5 25
+-Paso 3: 1 2 3 9 7 8 6 4 5 25
+-Paso 4: 1 2 3 4 7 8 6 9 5 25
+-Paso 5: 1 2 3 4 5 8 6 9 7 25
+-Paso 6: 1 2 3 4 5 6 8 9 7 25
+-Paso 7: 1 2 3 4 5 6 7 9 8 25
+-Paso 8: 1 2 3 4 5 6 7 8 9 25
+-Paso 9: 1 2 3 4 5 6 7 8 9 25

---Desendente con Insertion Sort---

+-paso 1: 2 1 3 4 5 6 7 8 9 25
+-paso 2: 3 2 1 4 5 6 7 8 9 25
+-paso 3: 4 3 2 1 5 6 7 8 9 25
+-paso 4: 5 4 3 2 1 6 7 8 9 25
+-paso 5: 6 5 4 3 2 1 7 8 9 25
+-paso 6: 7 6 5 4 3 2 1 8 9 25
+-paso 7: 8 7 6 5 4 3 2 1 9 25
+-paso 8: 9 8 7 6 5 4 3 2 1 25
+-paso 9: 25 9 8 7 6 5 4 3 2 1
