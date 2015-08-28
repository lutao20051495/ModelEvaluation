#!/usr/bin/env sh
../Debug/ModelEvaluation 0 ../models/lenet/deploy.prototxt \
			   ../models/lenet/snapshots_iter_3000.caffemodel \
			   "" \
			   ../models/lenet/label.txt \
			   ../neg_img \
			   0.9 \
			   0
