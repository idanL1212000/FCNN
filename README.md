<h2>MLP Network for Digit Recognition</h2>
<p>This repository contains a C++ implementation of a Multi-Layer Perceptron (MLP) network designed for digit recognition, along with a Python script for visualizing image data.</p>
<h3>Overview</h3>
<p>The C++ MLP network is a feed-forward neural network with multiple layers, capable of classifying handwritten digits.
  It expects pre-trained weights and biases as command-line arguments. The network processes input images
  (expected to be 28x28 pixel flattened binary files) and outputs the predicted digit and its associated probability.
  The plot_img.py script is a utility to visualize these 28x28 pixel binary image files, 
  which can be useful for verifying input data.</p>

</h3>Building and Running the C++ MLP Network</h3>
<h4>Prerequisites</h4>
<ul>
<li>A C++ compiler (e.g., g++).</li>
<li>Standard C++ libraries.</li>
</ul>
<h4>Compilation</h4>
<p>To compile the C++ source files, navigate to the project root directory in your terminal and execute a command similar to this:</p>
<p>g++ main.cpp -o mlpnetwork</p>
<p>This will create an executable named mlpnetwork.</p>
<h4>Usage</h4>
<p>The mlpnetwork executable requires paths to the pre-trained weights and biases for each of its four layers.
  The order of arguments is crucial: w1 w2 w3 w4 b1 b2 b3 b4.</p>
  <p>./mlpnetwork w1_path w2_path w3_path w4_path b1_path b2_path b3_path b4_path</p>
<ul>
<li>wi: path to the binary file containing weights for the i-th layer.</li>
<li>bi: path to the binary file containing biases for the i-th layer.</li></ul>
