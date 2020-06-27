# Exploratory Data Analysis — Pulsar 
library(leaps)
library(glmnet)
library(pls)
library(tidyr)
library(ggplot2)
library(plyr)

# set working directory
setwd("~/Desktop/DataScience/Summer_Capstone/britishfashioncouncil/Data/Pulsar")
main = read.csv('pulsar_main.csv')
summary(main)

fashionweek1 = subset(main, Fashion.Week == "1")
summary(fashionweek1)

ggplot(fashionweek1, aes(x=Topic, y=Mentions)) + geom_boxplot() + ggtitle("FW1 — Mentions")
ggplot(fashionweek1, aes(x=Topic, y=Impressions)) + geom_boxplot() + ggtitle("FW1 — Impressions")
ggplot(fashionweek1,aes(x=Mentions))+geom_histogram()+facet_grid(~Topic)+theme_bw()

fashionweek2 = subset(main, Fashion.Week == "2")
ggplot(fashionweek2, aes(x=Topic, y=Mentions)) + geom_boxplot() + ggtitle("FW2 — Mentions")
ggplot(fashionweek2, aes(x=Topic, y=Impressions)) + geom_boxplot() + ggtitle("FW2 — Impressions")
ggplot(fashionweek2,aes(x=Mentions))+geom_histogram()+facet_grid(~Topic)+theme_bw()
summary(fashionweek2)

fashionweek3 = subset(main, Fashion.Week == "3")
ggplot(fashionweek3, aes(x=Topic, y=Mentions)) + geom_boxplot() + ggtitle("FW3 — Mentions")
ggplot(fashionweek3, aes(x=Topic, y=Impressions)) + geom_boxplot() + ggtitle("FW3 — Impressions")
ggplot(fashionweek3,aes(x=Mentions))+geom_histogram()+facet_grid(~Topic)+theme_bw()
summary(fashionweek3)


