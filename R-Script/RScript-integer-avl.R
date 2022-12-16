library(ggplot2)
library(dplyr)
library(ggthemes)

df <- read.csv(file = '../data/Avl/data_avl.csv',header=TRUE,sep=";")

df %>%
  ggplot(aes(x=nodes, y=average_time, color=type)) +
  geom_line()+
  labs(title = "Temps moyen cumulé",
  subtitle= ".",
  x = "Nombre de noeud",
  y = "Temps exécution (ms)",
  color = "Données") +
  theme(plot.title=element_text(hjust=0.5)) +
  theme_fivethirtyeight()+
  theme(axis.title = element_text())
  
ggsave("Resultat/AVL/temp_global_int_avl.png")

df %>%
  ggplot(aes(x=nodes, y=average_time_insert, color=type)) +
  geom_line()+
  labs(title = "Temps moyen d'insertion ",
  subtitle= "",
  x = "Nombre de noeud",
  y = "Temps exécution (ms)",
  color = "Données") +
  theme_fivethirtyeight()+
  theme(axis.title = element_text())

  
ggsave("Resultat/AVL/temp_insertion_int_avl.png")



df %>%
  ggplot(aes(x=nodes, y=average_time_search, color=type)) +
  geom_line()+
  labs(title = "Temps moyen de recherche",
  subtitle= "",
  x = "Nombre de noeud",
  y = "Temps exécution (ms)",
  color = "Données") +
  theme_fivethirtyeight() +
  theme(axis.title = element_text())
 
ggsave("Resultat/AVL/temp_recherche_int_avl.png")

