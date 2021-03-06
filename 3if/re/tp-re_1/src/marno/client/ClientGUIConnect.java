package marno.client;

import javax.swing.JOptionPane;

/**
 * Window connection options (username and server)
 */
public class ClientGUIConnect extends javax.swing.JDialog {

    /**
     * The client's main GUI window.
     */
    private final ClientGUI parent;

    /**
     * Initializes the window from the ClientGUIConnect form's generated code.
     *
     * @param parent the main GUI window
     * @param modal whether the parent is clickable or not
     */
    public ClientGUIConnect(ClientGUI parent, boolean modal) {
        super(parent, modal);

        this.parent = parent;

        initComponents();

        if (parent.client != null)
            textFieldUsername.setText(parent.client.username);
        labelErrorConnection.setVisible(false);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        buttonGroupType = new javax.swing.ButtonGroup();
        buttonCancel = new javax.swing.JButton();
        buttonConnect = new javax.swing.JButton();
        labelTitle = new javax.swing.JLabel();
        labelUsername = new javax.swing.JLabel();
        labelHost = new javax.swing.JLabel();
        labelPort = new javax.swing.JLabel();
        textFieldUsername = new javax.swing.JTextField();
        textFieldHost = new javax.swing.JTextField();
        textFieldPort = new javax.swing.JTextField();
        labelErrorConnection = new javax.swing.JLabel();
        labelType = new javax.swing.JLabel();
        radioButtonSocket = new javax.swing.JRadioButton();
        radioButtonRmi = new javax.swing.JRadioButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        setTitle("Connect");
        setResizable(false);

        buttonCancel.setText("Cancel");
        buttonCancel.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                buttonCancelActionPerformed(evt);
            }
        });

        buttonConnect.setText("Connect");
        buttonConnect.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                buttonConnectActionPerformed(evt);
            }
        });

        labelTitle.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        labelTitle.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        labelTitle.setText("Connect");

        labelUsername.setText("Username:");

        labelHost.setText("Host:");

        labelPort.setText("Port:");

        textFieldUsername.setText("User");

        textFieldHost.setText("127.0.0.1");

        textFieldPort.setText("1099");

        labelErrorConnection.setForeground(java.awt.Color.red);
        labelErrorConnection.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        labelErrorConnection.setText("Error: Connection failed");

        labelType.setText("Type:");

        buttonGroupType.add(radioButtonSocket);
        radioButtonSocket.setSelected(true);
        radioButtonSocket.setText("Socket");

        buttonGroupType.add(radioButtonRmi);
        radioButtonRmi.setText("RMI");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(labelErrorConnection, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(labelTitle, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(buttonCancel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(buttonConnect))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(labelUsername)
                            .addComponent(labelHost)
                            .addComponent(labelPort)
                            .addComponent(labelType))
                        .addGap(18, 18, 18)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(textFieldHost)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(radioButtonSocket)
                                        .addGap(18, 18, 18)
                                        .addComponent(radioButtonRmi))
                                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                        .addComponent(textFieldUsername, javax.swing.GroupLayout.DEFAULT_SIZE, 328, Short.MAX_VALUE)
                                        .addComponent(textFieldPort)))
                                .addGap(0, 0, Short.MAX_VALUE)))))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(labelTitle)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(labelUsername)
                    .addComponent(textFieldUsername, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(labelHost)
                    .addComponent(textFieldHost, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(labelPort)
                    .addComponent(textFieldPort, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(labelType)
                    .addComponent(radioButtonSocket)
                    .addComponent(radioButtonRmi))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 6, Short.MAX_VALUE)
                .addComponent(labelErrorConnection, javax.swing.GroupLayout.PREFERRED_SIZE, 14, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(buttonCancel)
                    .addComponent(buttonConnect))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    /**
     * Called when the connect button has been called.
     *
     * Tries to start a new client connection from the provided parameters.
     *
     * @param evt the click event
     */
    private void buttonConnectActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_buttonConnectActionPerformed
        labelErrorConnection.setVisible(false);

        if (radioButtonSocket.isSelected()) {
            parent.client = new SocketClient(parent);
        } else if (radioButtonRmi.isSelected()) {
            parent.client = new RMIClient(parent);
        } else {
            JOptionPane.showMessageDialog(
                    null, "Please choose a connection type.", "Error",
                    JOptionPane.ERROR_MESSAGE
            );
            return;
        }

        parent.client.username = textFieldUsername.getText();

        try {
            parent.client.connect(
                    textFieldHost.getText(), textFieldPort.getText()
            );

            setVisible(false);
        } catch (Exception e) {
            System.err.println("[Client exception]: " + e.getMessage());

            parent.client = null;

            labelErrorConnection.setVisible(true);
        }
    }//GEN-LAST:event_buttonConnectActionPerformed

    private void buttonCancelActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_buttonCancelActionPerformed
        setVisible(false);
    }//GEN-LAST:event_buttonCancelActionPerformed

    /**
     * Graphical elements variables
     */
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton buttonCancel;
    private javax.swing.JButton buttonConnect;
    private javax.swing.ButtonGroup buttonGroupType;
    private javax.swing.JLabel labelErrorConnection;
    private javax.swing.JLabel labelHost;
    private javax.swing.JLabel labelPort;
    private javax.swing.JLabel labelTitle;
    private javax.swing.JLabel labelType;
    private javax.swing.JLabel labelUsername;
    private javax.swing.JRadioButton radioButtonRmi;
    private javax.swing.JRadioButton radioButtonSocket;
    private javax.swing.JTextField textFieldHost;
    private javax.swing.JTextField textFieldPort;
    private javax.swing.JTextField textFieldUsername;
    // End of variables declaration//GEN-END:variables

}
