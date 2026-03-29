E COLE C ENTRALE DE N ANTES

SMP - TP10

L’objectif de ce TP est d’expérimenter les tests unitaires et d’avoir une première expérience
avec Google Test (GTest). Vous allez aussi utiliser Doxygen pour générer des fichiers de documentation.

1 I NSTALLATION DE CM AKE
CMake est multiplateforme et disponible à l’adresse https://cmake.org.
Téléchargez le binaire qui correspond à votre distribution à l’adresse suivante https://
cmake.org/download/.

2 I NSTALLATION DE D OXYGEN
Doxygen est multiplateforme et disponible à l’adresse suivante https://www.doxygen.nl/
index.html. Suivez les instructions d’installation selon votre système d’exploitation https:
//www.doxygen.nl/manual/index.html.
Remarque : sous mac il est possible de l’installer avec homebrew avec la commande :

brew install doxygen
Vous pourrez ensuite créer un fichier de configuration doxygen automatiquement avec la
commande (en remplaçant <config-file> par le nom que votre fichier de configuration) :

doxygen -g <config-file>
puis pour générer la documentation d’un projet replit il suffira de taper la commande :

doxygen <config-file>
Vous pouvez aussi utiliser l’interface graphique si vous l’avez installée.

1

Tester avec des fichiers d’un tp précédent que vous aurez complétés avec des commentaires
doxygen https://www.doxygen.nl/manual/docblocks.html.

3 I NTÉGRATION DE G OOGLE T EST AVEC CM AKE
Dans ce TP, nous allons intégrer Google Test directement dans le projet à l’aide de CMake,
sans compilation manuelle de la bibliothèque.

3.1 C HOIX DU STANDARD C++
Dans votre fichier CMakeLists.txt, vous devez définir le standard C++ utilisé :
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Si votre environnement ne supporte que C++11, utilisez :
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Remarque : si vous utilisez C++11, vous devrez utiliser la version v1.12.1 de Google Test
(compatible C++11).

3.2 A JOUT DE G OOGLE T EST VIA CM AKE
Ajoutez dans votre CMakeLists.txt les lignes suivantes :
include(FetchContent)
FetchContent_Declare(
googletest
GIT_REPOSITORY https://github.com/google/googletest.git
GIT_TAG v1.17.0
DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# Ne pas construire GoogleMock
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
# Option utile principalement sous Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

La liste des versions tagguées se trouvent à https://github.com/google/googletest/

tags

2

3.3 C RÉATION DE L’ EXÉCUTABLE DE TESTS
Ajoutez ensuite votre exécutable de test :
add_executable(mytest.out
factorielle.cpp
mytest.cpp
)
target_link_libraries(mytest.out
GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(mytest.out)

Vous trouverez un exemple de Cmake complet dans le dossier code de ce TP.

3.4 C OMPILATION DU PROJET
Depuis le dossier racine du projet :
mkdir build
cd build
cmake ..
cmake --build .

Pour exécuter les tests :
ctest

La commande ctest exécute les tests enregistrés par CMake.
Elle nécessite la présence de enable_testing() dans le CMakeLists.txt.
ou directement :
./mytest.out

Si tout est correctement configuré, les tests doivent s’exécuter automatiquement et afficher
leur résultat.

3.5 V ÉRIFICATION
— La commande cmake –build . compile sans erreur ;
— La commande ctest affiche le nombre de tests exécutés ;
— Un test en échec provoque une erreur visible.

4 E XÉCUTION DE TESTS AVEC G OOGLE T EST
Le code fourni vous donne des premiers exemples de tests. Exécutez les.

3

5 P REMIER TEST AVEC G OOGLE T EST
Créez un fichier de test pour tester les fichiers de codeTp2.
Testez de nouveau la fonction factorielle à l’aide de
TEST(TestCaseName , TestName)

et des macros ASSERT_EQ(expected,actual) et EXPECT_EQ(expected,actual).
Puis désactivez ce test en plaçant un
DISABLED_

dans l’une des entrées de TEST, i.e.,
TEST(DISABLED_TestCaseName, TestName)

ou
TEST(TestCaseName, DISABLED_TestName)

et observez les résultats.

6 E XPÉRIMENTER G OOGLE T EST ET LE T EST D RIVEN D EVELOPMENT
( TDD)
Le TDD est une méthode agile de code qui est guidée par les tests. Cette dernière est cyclique
et comporte les phases suivantes :
1. Écrire un seul test qui décrit une partie du problème à résoudre
2. Vérifier que le test échoue, c’est-à-dire que le code se rapportant à ce test n’existe pas
3. Écrire juste assez de code pour que le test réussisse
4. Vérifier que le test ainsi que ceux pré-existants passent
5. Remanier le code, i.e., améliorer sans altérer le comportement, e.g., enlever les doublons
Tout l’intérêt du TDD consiste à suivre le cycle précédent dans l’ordre. Donc, toute déviation
par rapport à l’ordre des questions dans cette feuille réduit l’intérêt de ce travail.

6.1 T EST 1 - EXPECT_DOUBLE
Créez un test à l’aide de la macro
TEST(TestCaseName , TestName)

pour une fonction nommée div (dans la classe Calculator) qui retourne 2 (type double) lorsqu’elle prend entrée les valeurs 4 et 2 (type double également).
Attention les macros à utiliser pour tester les float et double sont différentes. Par exemple, il
est ici nécessaire d’utiliser
EXPECT_DOUBLE_EQ (expected, actual)

Créez une fonction vide pour que le code puisse compiler et vérifiez que le test ne passe pas.
L’objectif est de créer le code pas à pas, en utilisant à chaque étape une méthode simple,
rapide, et faisant passer les tests existants. Écrivez donc la fonction la plus simple possible
permettant de faire passer ce test.

4

6.2 T EST 2 - EXPECT_NEAR
Pour le second test, réalisez une fonction div qui vérifie que le résultat de la fonction div
lorsqu’elle prend en entrée 7 et 3 retourne 2.333 ± 0.001. La macro correspondante à utiliser
est la suivante :
EXPECT_NEAR (expected, actual, absolute_range)

Vérifiez que le test ne passe pas.
Écrivez la fonction div (pour division, bien sûr) la plus simple possible permettant de vérifier
le test ci-dessus.
Testez de nouveau la fonction "div" avec la macro
EXPECT_NEAR

pour savoir si le résultat est à 2.333 ± 0.0001 et observez le résultat du test.

6.3 T EST 3 - ASSERT_EXIT
Pour le troisième et dernier test, utilisez
ASSERT_EXIT(statement, predicate, expected_message)

afin de tester si le programme quitte bien avec le prédicat
::testing::ExitedWithCode(255)

et le message
Error: Division by 0 not possible

lorsque la fonction div prend en entrée 7 et 0. Vérifiez que le test ne passe pas.
Modifiez votre fonction afin de réussir le test précédent.

6.4 T EST 4 - A VOUS DE JOUER
Bien que le programme soit simple, d’autres fonctionnalités restent à tester. Identifiez celles
primordiales au bon fonctionnement du programme. Modifiez le programme pour les rendre
testables. Créez un code pour tester son fonctionnement. Enfin, modifier le programme afin
qu’il passe ce test.

5

