library(ggplot2)
library(dplyr)
library(ggthemes)

df <- read.csv(file = '../data/rbtree/data_10k_int_complexity.csv',header=TRUE,sep=";")

df %>%
  ggplot(aes(x=n, y=number_of_comparaisons)) +
  geom_line()+
  labs(title = "Complexité",
  subtitle= ".",
  x = "Nombre de noeud",
  y = "Nombre de comparaison",
  color = "Données") +
  theme(plot.title=element_text(hjust=0.5)) +
  theme_fivethirtyeight()+
  theme(axis.title = element_text())
  
ggsave("Resultat/Complexite_lm.png")

