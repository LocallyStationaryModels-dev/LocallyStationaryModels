# **LocallyStationaryModels**
***authors:*** Luca Crippa, Giacomo De Carlo<br>
***mailto:*** <luca7.crippa@mail.polimi.it>, <giacomo.decarlo@mail.polimi.it><br>
## **Installation**
### **Step 1: install R and Rstudio (optional)**
#### **Windows:**
Download R from <https://cran.r-project.org/bin/windows/base/> and (optional) Rstudio from <https://www.rstudio.com/products/rstudio/download/>.
#### **Arch Linux:**
Open the terminal then type

    sudo pacman -S r

and install the `r` package for R.
To get Rstudio (optional), install an AUR helper of your choice such as <https://github.com/Jguer/yay> and then on the terminal

    yay -S rstudio-desktop-bin

Refer to <https://wiki.archlinux.org/title/r> for further details.
#### **Ubuntu:**
Refer to <https://cran.r-project.org/bin/linux/ubuntu/> for R.
For Rstudio (optional) you can download the `.deb` file from <https://www.rstudio.com/products/rstudio/download/>.
### **Step 2: install devtools and LocallyStationaryModels**
Open R then type

    install.packages("devtools")

to install `devtools`. Then type

    library(devtools)
    devtools::install_github("giacomodecarlo/LocallyStationaryModels")

to install `LocallyStationaryModels`.

