install.packages("ggplot2")
library(ggplot2)
library(data.table)

segTime = read.csv("/Users/kymryburwell/Desktop/SegmentTreeExecutionTime.txt", header = FALSE)
segSize = read.csv("/Users/kymryburwell/Desktop/SegmentTreeSize.txt", header = FALSE)

df = data.frame(segTime,segSize)

# Height Comparison
ggplot(df, aes("V1.1")) + # basic graphical object
  geom_line(aes(y="V1.1", colour="Time")) +  # first layer
  geom_line(aes(x="V1", colour="Size")) + # second layer
  ylab("Construction Time") + xlab("Number of Intervals") + 
  labs(title="Construction time of Segment Tree")+
  theme(plot.title = element_text(hjust = 0.5))

