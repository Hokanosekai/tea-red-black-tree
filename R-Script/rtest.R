library(ggplot2)
library(dplyr)
library(ggthemes)

#data <- read.table("../data/data_10k_1M_6.csv", sep=";", header=TRUE)

#mutate(typeTableau = factor(typeTableau, labels=c('aléatoire')))


df <- read.csv(file = '../data/RData/data_10K_1M_int.csv',header=TRUE,sep=";")



df %>%
  ggplot(aes(x=nodes, y=average_time, color=type)) +
  geom_line()+
  labs(title = "Temps moyen cumulé",
  subtitle= ".",
  x = "Nombre de noeud",
  y = "Temps moyen d'exécution",
  color = "Données") +
  theme_fivethirtyeight()+
  theme(axis.title = element_text())
  
ggsave("temp_global.png")

df %>%
  ggplot(aes(x=nodes, y=average_time_insert, color=type)) +
  geom_line()+
  labs(title = "Temps moyen d'insertion ",
  subtitle= "",
  x = "Nombre de noeud",
  y = "Temps moyen d'exécution",
  color = "Données") +
  theme_fivethirtyeight()+
  theme(axis.title = element_text())

  
ggsave("temp_insertion.png")



df %>%
  ggplot(aes(x=nodes, y=average_time_search, color=type)) +
  geom_line()+
  labs(title = "Temps moyen de recherche",
  subtitle= "",
  x = "Nombre de noeud",
  y = "Temps moyen d'exécution",
  color = "Données") +
  theme_fivethirtyeight() +
  theme(axis.title = element_text())
 
ggsave("temp_recherche.png")


df %>%
  ggplot(aes(x=nodes, y=average_time_delete, color=type)) +
  geom_line()+
  labs(title = "Temps moyen de supression",
  subtitle= "",
  x = "Nombre de noeud",
  y = "Temps moyen d'exécution",
  color = "Données") +
  theme_fivethirtyeight() +
   theme(axis.title = element_text())
 
ggsave("temp_supression.png")

# Appliquer un thème au graphique en utilisant la fonction theme_bw()
# ggplot(df, aes(x=n, y=average_time_insert)) +
#   geom_line() +
#   theme_bw()

# # Enregistrer le graphique en utilisant la fonction ggsave()
# ggsave("my_plot.png", width=8, height=6)



#temps

# ggplot(df, aes(x = n, y = average_time, color = typeTableau)) +
# geom_smooth(linewidth=1.5,alpha=0.8)+ geom_point()+ labs(title="Insertion ",x=n,y=average_time, color = "Type tableau")+
# theme_fivethirtyeight()+theme(axis.title=element_text())

# ggsave("temp_insert.png")