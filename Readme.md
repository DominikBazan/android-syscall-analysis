### Android Syscall Analysis

<p style="text-align: right">
Autorzy: Marcin Nowiński, Aleksander Lewandowski, Dominik Bazan

##

### Analiza problemu
Na podstawie materiałów, które udało nam się znaleźć w internecie zdecydowaliśmy się podjąć próbę wykorzystania system calls do wykonania zadania. Przed nami stało niełatwe zadanie polegające na znalezieniu sposobu na analizę system calls wykonywanych w trakcie działania aplikacji. Doszliśmy do wniosku, że będzie to wymagało ingerencji w procesy systemowe.

##

### Proponowane rozwiązanie
Z uwagi na to, że zwykły użytkownik nie ma możliwości monitorowania syscalls, zdecydowaliśmy się na podjęcie próby użycia zmodyfikowanego przez nas jądra systemy. Zmienionego tak aby była dla nas możliwość monitorowania aplikacji działających w systemie.

##

### Wykorzystane technologie
* Android SDK
* Android Studio
* Android Open Source Project
* Język C
* Docker
* Ubuntu 16
* Bash

##

### Przebieg prac
Wszystkie operacje wykonywaliśmy przy użyciu systemu Linux Mint.
Zainstalowaliśmy potrzebne programy, np. Python, git, curl, gedit, vim.

Pobraliśmy Android Studio. Zainstalowaliśmy KVM oraz Skonfigurowaliśmy środowisko.

Na początku pobraliśmy repozytorium zawierające kod źródłowy systemu Android
(AOSP). Zrobilismy to korzystając z oficjalnej instrukcji umieszcznej na stronie https://source.android.com/setup/build/downloading .

Wykorzystując technologię Docker zdołaliśmy utworzyć kontener pod Ubuntu 16 i pobrać tam android-ndk oraz kernel Androida. 

Wykorzystując android ndk próbowaliśmy zmodyfikować jądro systemu Android pod kątem uzyskania możliwości modyfikowania modułów systemowych.

Po konfiguracji, skompilowaliśmy zmodyfikowane jądro systemu Android.
Zmodyfikowaliśmy jego kernel, aby można było ściągnąć z niego syscalls poprzez
odpowiedni kod w języku C.

W tym momencie mieliśmy już gotowe zmodyfikowane jądro systemowe oraz emulator, przy pomocy którego chciliśmy je wykorzystać co próbowaliśmy zrobić.

##

Wszystkie prace wykonaliśmy w ramach projektu z przedmiotu <b>'Ochrona danych i systemów'</b> na drugim roku studiów magisterskich na kierunku Informatyka.
