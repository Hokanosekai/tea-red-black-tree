library(ggplot2)
library(plyr)
library(ggthemes)
library(tidyverse)
df <- read.table("../data/data_10k_1M_6.csv", sep=";", header=TRUE)
average_time <- subset(df[5] )
n <- subset(df[1] )



mutate(typeTableau = factor(typeTableau, labels=c('n','average_time')))

#temps

ggplot(average_time, aes(x = n, y = average_time, color = typeTableau)) +
geom_smooth(size=1.5,alpha=0.8)+ geom_point()+ labs(title="Test fusion : temps en fonction de taille",x="N",y="Temps", color = "Type tableau")+
theme_fivethirtyeight()+theme(axis.title=element_text())

ggsave("tab_fusion2.png")

# ggplot(insert, aes(x = taille, y = temps, color = typeTableau)) +
# geom_smooth(size=1.5,alpha=0.8)+ geom_point()+ labs(title="Test insert : temps en fonction de taille",x="Taille",y="Temps", color = "Type tableau")+
# theme_fivethirtyeight()+theme(axis.title=element_text())

# ggsave("../images/tab_insert2.png") 

# ggplot(bulle, aes(x = taille, y = temps, color = typeTableau)) +
# geom_smooth(size=1.5,alpha=0.8)+ geom_point()+ labs(title="Test bulle : temps en fonction de taille",x="Taille",y="Temps", color = "Type tableau")+
# theme_fivethirtyeight()+theme(axis.title=element_text())

# ggsave("../images/tab_bulle2.png")


# #memoire

# ggplot(fusion, aes(x = taille, y = mem, color = typeTableau)) +
# geom_smooth(size=1.5,alpha=0.8)+ geom_point()+ labs(title="Test fusion : mem en fonction de taille",x="Taille",y="Memoire", color = "Type tableau")+
# theme_fivethirtyeight()+theme(axis.title=element_text())

# ggsave("../images/tab_fusion2meme.png")

# ggplot(insert, aes(x = taille, y = mem, color = typeTableau)) +
# geom_smooth(size=1.5,alpha=0.8)+ geom_point()+ labs(title="Test insert : mem en fonction de taille",x="Taille",y="Memoire", color = "Type tableau")+
# theme_fivethirtyeight()+theme(axis.title=element_text())

# ggsave("../images/tab_insert2meme.png")

# ggplot(rapide, aes(x = taille, y = mem, color = typeTableau)) +
# geom_smooth(size=1.5,alpha=0.8)+ geom_point()+ labs(title="Test rapide : mem en fonction de taille",x="Taille",y="Memoire", color = "Type tableau")+
# theme_fivethirtyeight()+theme(axis.title=element_text())

# ggsave("../images/tab_rapide2mem.png")


# ggplot(bulle, aes(x = taille, y = mem, color = typeTableau)) +
# geom_smooth(size=1.5,alpha=0.8)+ geom_point()+ labs(title="Bulle : mem en fonction de taille",x="Taille",y="Memoire", color = "Type tableau")+
# theme_fivethirtyeight()+theme(axis.title=element_text())

# ggsave("../images/tab_bulle2mem.png")