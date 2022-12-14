library(ggplot2)
library(plyr)
library(ggthemes)

data <- read.table("../data/data_10k_1M_6.csv", sep=";", header=TRUE)

# Sélectionner les colonnes n et average_time
data <- data[, c("average_time_insert", "n")]

# Charger le package ggplot2 pour avoir accès à des thèmes plus élaborés
library(ggplot2)

# Appliquer un thème au graphique en utilisant la fonction theme_bw()
ggplot(data, aes(x=n, y=average_time_insert)) +
  geom_line() +
  theme_bw()

# Enregistrer le graphique en utilisant la fonction ggsave()
ggsave("my_plot.png", width=8, height=6)