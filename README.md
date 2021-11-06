# Installation
remotes::install_github("rustky/ChangepointPackage")
# Examples
Compute changepoints using Optimal Segmentation 
```
data(neuroblastoma, package="neuroblastoma")
library(data.table)
nb.dt <- data.table(neuroblastoma$profiles)
data.dt <- nb.dt[profile.id=="1" & chromosome=="1"]
data.vec <- data.dt[["logratio"]]
Kmax <- 5
mine.change <- ChangepointPackage::DynamProg_interface(data.vec,5)
```
Compute loss values via binary segmentation
```
data(neuroblastoma, package="neuroblastoma")
library(data.table)
nb.dt <- data.table(neuroblastoma$profiles)
data.dt <- nb.dt[profile.id=="2" & chromosome=="3"]
Kmax <- 5
mine.change <- ChangepointPackage::BINSEG(data.dt,5)
```
